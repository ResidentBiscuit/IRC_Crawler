#ifndef IRCCHANNEL_H
#define IRCCHANNEL_H

#include <string>
#include <vector>

#include "IrcUser.hpp"

class IrcChannel
{
public:
	IrcChannel(const std::string& channel_name);
	const std::string& get_channel_name();
	void add_user(const IrcUser& user);
	
private:
	std::string m_channel_name;
	//Might not need to be shared
	std::vector<std::shared_ptr<IrcUser>> m_user_list;
};

#endif