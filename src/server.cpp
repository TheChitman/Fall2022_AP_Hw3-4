#include "server.h"
#include <algorithm>
#include <iostream>
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



bool Server::create_message(Message* msg, std::string signature)
{

    bool authentic = crypto::verifySignature(
        public_keys[msg->get_sender()],
        msg->get_sender(),
        signature
        );
    if (authentic)
        this->messages.push_back(msg);
    return authentic;



    // if (authentic){
    //     this->messages.push_back(msg);
    //     std::cout << this->messages[0]->get_receiver() << std::endl;
    //     return authentic;
    // }
    // else 
    //     return false;
}


// std::vector<Message*> Server::get_all_messages_from(std::string username)
// {
//     std::vector<Message*> m_vector;
//     std::copy(this->users.begin(), this->users.end(), std::back_inserter(m_vector));
//     std::copy_if(m_vector.begin(), m_vector.end(),
//         nullptr,
//         [](Message* msg, std::string username){return msg->get_sender() == username;});//username is not that user name
//     return m_vector;
// }

// // std::vector<Message*> Server::get_all_messages_to(std::string username)
// {
//     std::vector<Message*> m_vector;
//     std::copy(this->users.begin(), this->users.end(), std::back_inserter(m_vector));
//     std::copy_if(m_vector.begin(), m_vector.end(),
//         nullptr,
//         [](Message* msg, std::string username){return msg->get_receiver() == username;});
//     return m_vector;
// }

// std::vector<Message*> Server::get_chat(std::string user1, std::string user2)
// {
//     std::vector<Message*> m_vector;
//     std::copy(this->users.begin(), this->users.end(), std::back_inserter(m_vector));
//     std::copy_if(m_vector.begin(), m_vector.end(),
//         nullptr,
//         [](Message* msg, std::string user1){return msg->get_sender() == user1;});
    
//     std::vector<Message*> m2_vector;
//     std::copy(m_vector.begin(), m_vector.end(), std::back_inserter(m2_vector));
//     std::copy_if(m2_vector.begin(), m2_vector.end(),
//         nullptr,
//         [](Message* msg, std::string user2){return msg->get_receiver() == user2;});

//     return m2_vector;
// }

// void Server::sort_msgs(std::vector<Message*> msgs)
// {
//     std::sort(this->messages.begin(), messages.end(),
//     [](Message* m){return m->get_time();}
//     );
// }

