#ifndef USER_H
#define USER_H
#include "message.h"
#include "server.h"
#include <string>
#include <vector>
class Server;

class User 
{
    public:
        User(std::string username, std::string private_key, Server* server); 
        std::string get_username();
        bool send_text_message(std::string text, std::string receiver);
        bool send_voice_message(std::string receiver);
    private:
        std::string username;
        std::string private_key;
        Server* const server;
};

#endif //USER_H