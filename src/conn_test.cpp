#include "TcpConnection.hpp"

#include <iostream>
 
int main()
{
    TcpConnection connection("irc.quakenet.org", "6667");
    connection.connect();
    bool joined = false;

    while(true)
    {
        while(connection.has_message())
        {
            std::string message = connection.get_next_message();
            if(message.find("NOTICE AUTH :*** Found your hostname") != std::string::npos)
            {
                connection.send("NICK ResidentBot\r\n");
                connection.send("USER RBot 0 * :RBot\r\n");
            }
            if(message.find("PING") == 0)
            {
                //Reply to server PING requests
                std::string pong = "PONG" + message.substr(4, std::string::npos);
                connection.send(pong);
                if(!joined)
                {
                    connection.send("JOIN #cplusplus\r\n");
                    joined = true;
                }
            }
            std::cout << message;
        }
    }

    return 0;
}