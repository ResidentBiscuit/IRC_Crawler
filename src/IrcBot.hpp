#ifndef IRCBOT_H
#define IRCBOT_H

#include <string>
#include <vector>
#include <memory>

#include "TcpConnection.hpp"
#include "IrcChannel.hpp"

class IrcBot
{
public:
	IrcBot(const std::string& nick, const std::string& user);
	void connect(const std::string network, int port = 6667);
	void add_channel(const std::string& channel_name);
	const std::vector<std::unique_ptr<IrcChannel>>& get_channel_list();
	void run();
	bool is_running();

private:
	void register_connection();

	void handle_message(const std::string& message);
	void send_message(const std::string& message);

	std::unique_ptr<TcpConnection> m_connection;

	std::vector<std::unique_ptr<IrcChannel>> m_channel_list;

	std::string m_nick;
	std::string m_user;
	bool m_running;
	bool m_connected;
};

#endif