#include "IrcChannel.hpp"

IrcChannel::IrcChannel(const std::string& channel_name) : m_channel_name(channel_name) {}

const std::string& IrcChannel::get_channel_name()
{
	return m_channel_name;
}