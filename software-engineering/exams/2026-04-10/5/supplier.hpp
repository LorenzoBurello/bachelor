#pragma once

#include "params.hpp"
#include "peer.hpp"
#include "network.hpp"

class Network;

class Supplier : public Peer{

public:
    Supplier(Params* p_init, Network* net_DB_sup_init, int id_init);

    void receiveMessage(std::shared_ptr<Message> m) override;
    void sendMessage() override;
    void sendSupply(double t);    

    Params* p;
    Network* net_DB_sup;
};