#include "IrcBot.hpp"

int main(int argc, char* argv[])
{
	IrcBot bot("ResidentBot", "ResidentBiscuit");
	bot.connect("irc.freenode.net", 6667);
	bot.run();

	return 0;
}