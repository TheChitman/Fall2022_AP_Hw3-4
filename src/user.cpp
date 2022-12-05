#include "user.h"

User::User(std::string _username, std::string _private_key, Server* _server)
    : username{_username}, private_key{_private_key}, server{_server}
{}


std::string User::get_username() { return username; }


bool User::send_text_message(std::string text, std::string receiver)
{
    TextMessage msg{text, this->get_username(), receiver};
    std::string signature = crypto::signMessage(private_key, this->get_username());
    return this->server->create_message(&msg, signature);
}

bool User::send_voice_message(std::string receiver)
{
    VoiceMessage msg{this->get_username(), receiver};
    std::string signature = crypto::signMessage(private_key, this->get_username());
    return this->server->create_message(&msg, signature);    
}
