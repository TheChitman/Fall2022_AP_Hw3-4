#include "message.h"

Message::Message(std::string _type, std::string _sender, std::string _receiver)
    : type{_type}, sender{_sender}, receiver{_receiver}
{
    std::time_t _now = std::time(0);
    std::string _time = std::ctime(&_now);
    _time.erase(_time.find_last_not_of(" \n\r\t")+1);
    time = _time;
    std::cout << "Message constructor" << std::endl;
}

Message::Message() : Message("","","") {}


std::string Message::get_type() const { return type; }


std::string Message::get_receiver() const { return receiver; }


std::string Message::get_sender() const { return sender; }


std::string Message::get_time() const { return time; }


void Message::print(std::ostream &os) const 
{
    os  << "***************************" << std::endl
        << sender << " -> " << receiver  << std::endl
        << "Message Type : " << type     << std::endl
        << "Message Time : " << time     << std::endl
        << "***************************" << std::endl;
}


std::ostream& operator<<(std::ostream &os, const Message &c){ //fix the const problem
    c.print(os);
    return os;
}


TextMessage::TextMessage(std::string _text, std::string _sender, std::string _receiver)
    : Message{"text", _sender, _receiver},
     text{_text}
{
    std::cout << "TextMessage constructor!" << std::endl;
}


void TextMessage::print(std::ostream &os) const
{
    os  << "***************************"             << std::endl
        << get_sender() << " -> " << get_receiver()  << std::endl
        << "Message Type : " << get_type()           << std::endl
        << "Message Time : " << get_time()           << std::endl
        << "Message Text : " << text                 << std::endl
        << "***************************"             << std::endl;
}


std::string TextMessage::get_text() { return text; }


VoiceMessage::VoiceMessage(std::string _sender, std::string _receiver)
    : Message("voice", _sender, _receiver)
{
    for (size_t i{0}; i < 5; i++){
        char randomint  = (unsigned char) rand() % 255;
        unsigned char ch = randomint;
        this->voice.push_back(randomint);
    }
}


void VoiceMessage::print(std::ostream &os) const
{
    os  << "***************************"                 << std::endl
        << get_sender() << " -> " << get_receiver()      << std::endl
        << "Message Type : " << get_type()               << std::endl
        << "Message Time : " << get_time()               << std::endl
        << "Voice : ";  
        for (unsigned char character : voice)
            os << (int) character << " ";
        os << std::endl << "***************************" <<std::endl;
}


std::vector<unsigned char> VoiceMessage::get_voice() { return voice; }


User::User(std::string _username, std::string _private_key, Server* _server)
    : username{_username}, private_key{_private_key}, server{_server}
{}


std::string User::get_username() { return username; }


// bool send_text_message(std::string text, std::string receiver)
// {
    
// }


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
    bool authentic = crypto::verifySignature(msg->public,public_key, "my data", signature);
    return authentic;
}

