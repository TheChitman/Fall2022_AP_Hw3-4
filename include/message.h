#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <random>
#include "crypto.h"

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


#endif //MESSAGE_H