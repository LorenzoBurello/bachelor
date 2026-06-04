#pragma once

#include <array>
#include <memory>

#include "params.hpp"
#include "peer.hpp"


class Message;
class Network;

class DB : public Peer{

public:
    DB(Params* p_init, Network* net_serv_DB_init, Network* net_DB_sup_init);
    
    void receiveMessage(std::shared_ptr<Message> m) override;
    void sendMessage() override;

    Network* net_serv_DB;
    Network* net_DB_sup;
    Params* p;

    std::vector<int> products_quantity;
    std::vector<int> products_cost;
    
};