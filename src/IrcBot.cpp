#include "IrcBot.hpp"

IrcBot::IrcBot(const std::string& nick, const std::string& user) : m_nick(nick), m_user(user) {}

void IrcBot::connect(const std::string network, int port = 6667)
{
	m_connection.connect(network, std::to_string(port));
}

void IrcBot::run()
{
	while(m_connection.has_message())
	{
		handle_message(m_connection.get_next_message());
	}
}

void IrcBot::handle_message(const std::string& message)
{
	//Need to parse the message, RegEx ahoy!
}