#include "IrcBot.hpp"

#include <sstream>
#include <iostream>

IrcBot::IrcBot(const std::string& nick, const std::string& user) : m_nick(nick), m_user(user) {}

void IrcBot::connect(const std::string network, int port)
{
	m_connection.reset(new TcpConnection(network, std::to_string(port)));
	m_connection->connect();
}

void IrcBot::add_channel(const IrcChannel& channel)
{
	m_channel_list.emplace_back(channel);
}

const std::vector<IrcChannel>& IrcBot::get_channel_list()
{
	return m_channel_list;
}

void IrcBot::run()
{
	m_running = true;
	m_connected = false;
	while(is_running())
	{
		while(m_connection->has_message())
		{
			//Register connection once ready.
			//We have to wait for the server to send something before we can send the connection registration parameters.
			if(!m_connected)
			{
				send_message("NICK ResidentBot\r\n");
				send_message("USER ResidentBiscuit 0 0: ResidentBiscuit\r\n");
				m_connected = true;
			}
			handle_message(m_connection->get_next_message());
		}
	}
}

bool IrcBot::is_running()
{
	return m_running;
}

void IrcBot::handle_message(const std::string& message)
{
	std::cout << message;

	std::string prefix;
	std::string command;
	std::vector<std::string> command_parameters(15);
	//If server sends a PING, need to send back a PONG
	if(message.find("PING") == 0)
	{
		send_message("PONG " + (message.substr(4, std::string::npos)));
		return;
	}

	//Tokenize message
	std::stringstream ss(message);
	std::string token;
	std::vector<std::string> tokens;
	while(std::getline(ss, token, ' '))
	{
		tokens.push_back(token);
	}

	//If message has a prefix, we need to strip that off. Command is the following token then
	if(tokens[0].find(':') == 0)
	{
		prefix = message.substr(1, message.find(' '));
		command = tokens[1];
		for(int i = 2; i < tokens.size(); i++)
		{
			command_parameters.push_back(tokens[i]);
		}
	}
	//There is no prefix, so the first token is the command and following are parameters
	else
	{
		command = tokens[0];
		for(int i = 1; i < tokens.size(); i++)
		{
			command_parameters.push_back(tokens[i]);
		}
	}

	//Get channel listing after server has finished sending the MOTD
	if(command == "376")
	{
		send_message("LIST\r\n");
	}
	if(command == "322")
	{
		add_channel(IrcChannel(command_parameters[0]));
	}
}

void IrcBot::send_message(const std::string& message)
{
	m_connection->send(message);
}