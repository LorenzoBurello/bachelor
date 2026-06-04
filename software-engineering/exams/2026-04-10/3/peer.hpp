#pragma once

#include <memory>

class Message;

class Peer{
public:
    
    Peer(int id_init);
    int id;
    virtual void receiveMessage(std::shared_ptr<Message> m)  = 0;
    virtual void sendMessage() = 0;

};