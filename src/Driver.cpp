#include "IrcBot.hpp"

int main(int argc, char* argv[])
{
	IrcBot bot("ResidentBot", "ResidentBiscuit");
	bot.run();

	return 0;
}