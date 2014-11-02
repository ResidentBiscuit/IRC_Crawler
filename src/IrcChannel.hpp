#ifndef IRCCHANNEL_H
#define IRCCHANNEL_H

#include <string>
#include <vector>
#include <memory>

class IrcChannel
{
public:
	IrcChannel();
	IrcChannel(const std::string& channel_name);
	const std::string& get_channel_name();
	void set_channel_name(const std::string& channel_name);
	
private:
	std::string m_channel_name;
};

#endif