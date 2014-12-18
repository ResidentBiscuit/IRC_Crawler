#include "IrcBot.hpp"

#include "IRC.hpp"
#include "IrcChannel.hpp"
#include "Message.hpp"	
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

	Message msg(message);

	if(msg.get_command() == "PING")
	{
		send_message("PONG " + msg.get_command_parameters().front());
	}

	//Join channels after connection is registered
	if(msg.get_command() == IRC::RPL_WELCOME)
	{
		send_message("JOIN #botdever\r\n");
	}

	if(msg.get_command() == "PRIVMSG")
	{
		if(msg.get_nick() == m_nick)
		{
			if(msg.get_message() == "Quit\r\n")
			{
				send_message("QUIT\r\n");
				m_connection->disconnect();
				m_running = false;
			}
		}
	}
}

void IrcBot::send_message(const std::string& message)
{
	m_connection->send(message);
}