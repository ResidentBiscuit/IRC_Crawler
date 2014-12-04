#ifndef IRC_H
#define IRC_H

/**
 * IRC
 * Defines the IRC protocol numerical codes.
 *
 * @author Jared Ready
 */

 #include <string>

namespace IRC
{
	static const std::string RPL_LIST = "322";
	static const std::string RPL_LISTEND = "323";
	static const std::string RPL_ENDOFMOTD = "376";
	static const std::string ERR_NOSUCHNICK = "401";
	static const std::string ERR_NOSUCHSERVER = "402";
	static const std::string ERR_NOSUCHCHANNEL = "403";
	static const std::string ERR_CANNOTSENDTOCHAN = "404";
	static const std::string ERR_TOOMANYCHANNELS = "405";
	static const std::string ERR_WASNOSUCHNICK = "406";
	static const std::string ERR_TOOMANYTARGETS = "407";
	static const std::string ERR_NOORIGIN = "409";
	static const std::string ERR_NORECIPIENT = "411";
	static const std::string ERR_NOTEXTTOSEND = "412";
	static const std::string ERR_NOTOPLEVEL = "413";
};

#endif