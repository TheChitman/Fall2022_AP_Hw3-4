#ifndef SERVER_H
#define SERVER_H

#include "user.h"
#include "message.h"
#include <vector>
#include <map>
#include <string>
class User;

class Server
{
    public:
        Server();
        std::vector<User> get_users();
        std::map<std::string, std::string> get_public_keys();
        std::vector<Message*> get_messages();
        User create_user(std::string username);
        bool create_message(Message* msg, std::string signature);

    private:
        std::vector<User> users;
        std::map<std::string, std::string> public_keys;
        std::vector<Message*> messages;
};


#endif //SERVER_H