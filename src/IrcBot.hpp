#ifndef IRCBOT_H
#define IRCBOT_H

#include <string>
#include <vector>
#include <memory>

#include "TcpConnection.hpp"

class IrcBot
{
public:
	IrcBot(const std::string& nick, const std::string& user);

	void connect(const std::string network, int port = 6667);

	void run();

	bool is_running();

private:
	void handle_message(const std::string& message);
	void send_message(const std::string& message);

	std::unique_ptr<TcpConnection> m_connection;

	std::string m_nick;
	std::string m_user;
	bool m_running;
};

#endif