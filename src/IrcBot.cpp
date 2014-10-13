#include "IrcBot.hpp"

#include <sstream>

IrcBot::IrcBot(const std::string& nick, const std::string& user) : m_nick(nick), m_user(user) {}

void IrcBot::connect(const std::string network, int port)
{
	m_connection = std::move(std::unique_ptr<TcpConnection>(new TcpConnection(network, std::to_string(port))));
}

void IrcBot::run()
{
	while(m_connection->has_message())
	{
		handle_message(m_connection->get_next_message());
	}
}

void IrcBot::handle_message(const std::string& message)
{
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
	
}

void IrcBot::send_message(const std::string& message)
{
	m_connection->send(message);
}