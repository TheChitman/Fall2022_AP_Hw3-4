#include "server.h"


Server::Server() {}


std::vector<User> Server::get_users() { return users; }


std::map<std::string, std::string> Server::get_public_keys() { return public_keys; }


std::vector<Message*> Server::get_messages() { return messages; }


User Server::create_user(std::string username) 
{
    for (User user : users)
        if (user.get_username() == username)
            throw std::logic_error("duplication username error");
    
    std::string public_key{}, private_key{};
    crypto::generate_key(public_key, private_key);
    public_keys[username] = public_key; 

    User user = User(username, private_key, this);
    users.push_back(user);
    return user;
}



// bool Server::create_message(Message* msg, std::string signature)
// {
//     bool authentic = crypto::verifySignature(msg->public,public_key, "my data", signature);
//     return authentic;
// }
