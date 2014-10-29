#ifndef IRCUSER_H
#define IRCUSER_H

#include <string>

class IrcUser
{
public:
	IrcUser(std::string nickname, std::string username);
	const std::string& get_nickname();
	const std::string& get_username();
	
private:
	std::string m_nickname;
	std::string m_username;
};

#endif