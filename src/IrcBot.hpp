#ifndef IRCBOT_H
#define IRCBOT_H

class IrcBot
{
public:
	IrcBot(const std::string& nick, const std::string& user);
	IrcBot(const std::string& config_file);
};

#endif