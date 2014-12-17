#include "IrcBot.hpp"

#include "IRC.hpp"
#include "IrcChannel.hpp"
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

IrcBot::IrcBot(const std::string& nick, const std::string& user) : m_nick(nick), m_user(user) {}

void IrcBot::connect(const std::string network, int port)
{
	m_connection.reset(new TcpConnection(network, std::to_string(port)));
	m_connection->connect();
}

void IrcBot::run()
{
	register_connection();

	m_running = true;
	while(is_running())
	{
		while(m_connection->has_message())
		{
			handle_message(m_connection->get_next_message());
		}
		//We can wait a second for more messages to show up. No need to endlessly beat the CPU
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

bool IrcBot::is_running()
{
	return m_running;
}

void IrcBot::register_connection()
{
	send_message("NICK " + m_nick + "\r\n");
	send_message("USER " + m_user + " 0 0: " + m_user + "\r\n");
}

void IrcBot::handle_message(const std::string& message)
{
	std::cout << message;

	//Tokenize message
	std::stringstream ss(message);
	std::string token;
	std::vector<std::string> tokens;
	while(std::getline(ss, token, ' '))
	{
		tokens.emplace_back(token);
	}

	//If message has a prefix, we need to strip that off and the command is the following token
	std::string prefix;
	std::string command;
	std::vector<std::string> command_parameters(15);
	if(tokens[0].find(':') == 0)
	{
		prefix = message.substr(1, message.find(' '));
		command = tokens[1];
		for(int i = 2; i < tokens.size(); i++)
		{
			command_parameters.emplace_back(tokens[i]);
		}
	}
	//There is no prefix, so the first token is the command and following are parameters
	else
	{
		command = tokens[0];
		for(int i = 1; i < tokens.size(); i++)
		{
			command_parameters.emplace_back(tokens[i]);
		}
	}

	if(command == "PING")
	{
		send_message("PONG " + command_parameters.front());
	}

	//Join channels after connection is registered
	if(command == IRC::RPL_WELCOME)
	{
		send_message("JOIN #botdever\r\n");
	}
}

void IrcBot::send_message(const std::string& message)
{
	m_connection->send(message);
}