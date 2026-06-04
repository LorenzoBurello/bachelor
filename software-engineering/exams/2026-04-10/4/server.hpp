#pragma once

#include <array>
#include "params.hpp"
#include "supplier.hpp"
#include "network.hpp"

class Message;
class Network;


class Server : public Peer{

public:
    Server(Params* p_init, Network* net_cust_ser_init, Network* net_ser_DB_init, int id_init);

    void receiveMessage(std::shared_ptr<Message> m) override;
    void requestProduct(double t);
    void request_DB(double t);
    void sendMessage() override;   
    
    double tao = 0;
    double sellBuy = 0;

    double y = 0;
    void updateY();

    std::vector<std::array<int, 2>> cache;

    std::bernoulli_distribution even_item;
    std::bernoulli_distribution even_quantity;

    Network* net_cust_ser;
    Network* net_ser_DB;
    Params* p;
};