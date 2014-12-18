#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

class Message
{
public:
	Message(const std::string& message);
	/**
	 * @return who the message was from
	 */
	std::string get_from();
	/**
	 * @return who the message was to
	 */
	std::string get_to();
	/**
	 * @return the message
	 */
	std::string get_message();
	/**
	 * @return raw message (same message that was passed into ctor)
	 */
	std::string get_raw();
	/**
	 * @return message prefix
	 */
	std::string get_prefix();
	/**
	 * @return message command
	 */
	std::string get_command();
	/**
	 * @return message command parameters
	 */
	std::vector<const std::string>& get_command_parameters();

private:
	void parse_message(const std::string& message);
	std::vector<std::string> split(const std::string &s, char delim);
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

	std::string m_raw;
	std::string m_prefix;
	std::vector<const std::string> m_command;

	std::string m_to;
	std::string m_from;
	std::string m_message;
};

#endif