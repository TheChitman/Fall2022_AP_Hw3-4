#include "user.h"

User::User(std::string _username, std::string _private_key, Server* _server)
    : username{_username}, private_key{_private_key}, server{_server}
{}


std::string User::get_username() { return username; }


// bool send_text_message(std::string text, std::string receiver)
// {
    
// }