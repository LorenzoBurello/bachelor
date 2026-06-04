#pragma once

#include "params.hpp"
#include "customer.hpp"
#include "network.hpp"
#include "db.hpp"
#include "supplier.hpp"

class Event{
    public:

    Event(double t_init, int id_init, std::shared_ptr<Peer> p_init, int code_init, std::shared_ptr<Message> m_init);

    
    int id;
    double t;

    double simulation_time;
    double next_time;
    
    std::shared_ptr<Peer> p;
    int code;
    std::shared_ptr<Message> m;
};

struct EventCompare {
    bool operator()(const std::shared_ptr<Event>& e1, const std::shared_ptr<Event>& e2) const 
    {
        return e1->t > e2->t;  
    }
};

class System{

    public:

    System(Params* p_init);

    void init();
    int nextState();
    void refresh_servers(bool even);

    double obtainRR(double t);
    
    double odd_server_refresh;
    double even_server_refresh;
    double simulation_time;
    double next_time;


    Network* cust_serv;
    Network* serv_DB;
    Network* DB_sup;
    
    Params* p;

    std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventCompare> events;
    std::shared_ptr<DB> centralized_DB;
    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<Server>> servers;

};