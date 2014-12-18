#include "Message.hpp"

#include <sstream>

Message::Message(const std::string& message) : m_raw(message), m_prefix(""), m_trail(""), m_to(""), m_from(""), m_message("")
{
	parse_message(message);
}

std::string Message::get_from()
{
	return m_from;
}

std::string Message::get_to()
{
	return m_to;
}

std::string Message::get_message()
{
	return m_message;
}

std::string Message::get_raw()
{
	return m_raw;
}

std::string Message::get_prefix()
{
	return m_prefix;
}

std::string Message::get_command()
{
	return m_command;
}

std::vector<const std::string>& Message::get_command_parameters()
{
	return m_command_parameters;
}

void Message::parse_message(const std::string& message)
{
	//Look for presence of a prefix
	int prefix_end_pos = -1;
	if(message.find(":") == 0)
	{
		prefix_end_pos = message.find(" ");
		m_prefix = message.substr(1, prefix_end_pos - 1);
	}
	//Look for presence of trailing part
	std::string trail("");
	int trailing_begin_pos = message.find(" :");
	if(trailing_begin_pos >= 0)
	{
		trail = message.substr(trailing_begin_pos + 2, std::string::npos);
	}
	else
	{
		trailing_begin_pos = message.length();
	}
	//Grab command and parameters
	m_command = split(message.substr(prefix_end_pos + 1, trailing_begin_pos - prefix_end_pos - 1), ' ');
	//If the trailing portion is valid, stick it at the end of the command vector
	if(!trail.empty())
	{
		m_command.emplace_back(trail);
	}

	if(m_command == "PRIVMSG" || m_command == "NOTICE")
	{
		m_from = m_prefix.substr(0, m_prefix.find("!"));
		m_to = m_command.front();
		m_message = m_command.back();
	}
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}