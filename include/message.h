#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <random>
#include <map>
#include "crypto.h"
class Server;

class Message {
    public:
        Message(std::string type, std::string sender, std::string receiver);
        Message();
        std::string get_type() const;
        std::string get_receiver() const;
        std::string get_sender() const;
        std::string get_time() const;
        virtual void print(std::ostream &os) const;
        friend std::ostream& operator<<(std::ostream &os, const Message &c);

    private:
        std::string type;
        std::string sender;
        std::string receiver;
        std::string time;    
};

class TextMessage : public Message 
{
    public:
        TextMessage(std::string text, std::string sender, std::string receiver);
        virtual void print(std::ostream &os) const;
        std::string get_text();
    
    private:
        std::string text;
};

class VoiceMessage : public Message 
{
    public:
        VoiceMessage(std::string sender, std::string receiver);
        virtual void print(std::ostream &os) const;
        std::vector<unsigned char> get_voice();

    private:
        std::vector<unsigned char> voice;

};

class User 
{
    public:
        User(std::string username, std::string private_key, Server* server); 
        std::string get_username();
        // bool send_text_message(std::string text, std::string receiver);

    private:
        std::string username;
        std::string private_key;
        Server* const server;
};

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



#endif //MESSAGE_H