#ifndef IRCCHANNEL_H
#define IRCCHANNEL_H

#include <string>
#include <vector>
#include <memory>

#include "IrcUser.hpp"

class IrcChannel
{
public:
	IrcChannel();
	IrcChannel(const std::string& channel_name);
	const std::string& get_channel_name();
	void add_user(const IrcUser& user);
	void set_channel_name(const std::string& channel_name);
	
private:
	std::string m_channel_name;
};

#endif