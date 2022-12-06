#include "user.h"
#include <algorithm>
User::User(std::string _username, std::string _private_key, Server* _server)
    : username{_username}, private_key{_private_key}, server{_server}
{}


std::string User::get_username() { return username; }


bool User::send_text_message(std::string text, std::string receiver)
{
    Message* msg;
    msg = new TextMessage(text, this->get_username(), receiver);
    std::string signature = crypto::signMessage(private_key, this->get_username());
    bool authentic =  this->server->create_message(msg, signature);
    return authentic;   
}

bool User::send_voice_message(std::string receiver)
{
    Message* msg;
    msg = new VoiceMessage(this->get_username(), receiver);
    std::string signature = crypto::signMessage(private_key, this->get_username());
    bool authentic = this->server->create_message(msg, signature);    
    return authentic;
}
