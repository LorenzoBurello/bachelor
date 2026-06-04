#pragma once

#include "peer.hpp"
#include "params.hpp"

class Network;
class Message;

class Customer: public Peer{
    public:

    Customer(Params* p_init, Network* cust_serv_init, int id_init);

    void makeTransition();
    void receiveMessage(std::shared_ptr<Message> m) override;
    void requestProduct(double t);
    void sendMessage() override;

    Params* p;
    Network* cust_serv;
    double tao = 0;
    double send_time;

};