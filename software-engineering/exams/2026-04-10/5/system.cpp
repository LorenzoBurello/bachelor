#include "system.hpp"

Event::Event(double t_init, int id_init, std::shared_ptr<Peer> p_init, int code_init, std::shared_ptr<Message> m_init):
    t(t_init),
    p(p_init),
    id(id_init),
    code(code_init),
    m(std::move(m_init))
{

};


System::System(Params* p_init)
{
    p = p_init;

    cust_serv = new Network();
    serv_DB = new Network();
    DB_sup = new Network();

    cust_serv->sys = this;
    serv_DB->sys = this;
    DB_sup->sys = this;

    double simulation_time = 0;
    double next_time = 0;
};

void System::init(){
    cust_serv->limit = p->C;
    serv_DB->limit = p-> S;
    DB_sup->limit = p->F;

    
    even_server_refresh = p->ST0;
    odd_server_refresh = p->ST1;
    
    centralized_DB = std::make_shared<DB>(p, serv_DB, DB_sup);

    // customers init
    for(size_t id = 0; id < p -> C; id++){
        auto customer = std::make_shared<Customer>(p, cust_serv, id+1);
        cust_serv->processes.push_back(customer);

        events.push(std::make_shared<Event>(p->dist_cust_tao(p->eng), 0, customer, 0, nullptr));
    }

    // servers init
    for(size_t id = 0; id < p -> S; id++){
        auto server = std::make_shared<Server>(p, cust_serv, serv_DB, id+1);
        if(id%2){
            server->even_item = p->dist_odd_server_even_item;
            server->even_quantity = p->dist_odd_server_even_quantity;
            events.push(std::make_shared<Event>(p->ST1, 0, server, 0, nullptr));

        }else{
            server->even_item = p->dist_even_server_even_item;
            server->even_quantity = p->dist_even_server_even_quantity;
            events.push(std::make_shared<Event>(p->ST0, 0, server, 0, nullptr));
        }
        events.push(std::make_shared<Event>(p->T, 1, server, 0, nullptr));
        cust_serv->processes.push_back(server);
        serv_DB->processes.push_back(server);
        servers.push_back(server);
    }

    serv_DB->processes.push_back(centralized_DB);
    DB_sup->processes.push_back(centralized_DB);

    // suppliers init
    for(size_t i = 0; i < p -> F; i++){
        auto supplier = std::make_shared<Supplier>(p, DB_sup, i+1);
        DB_sup->processes.push_back(supplier);
    
        events.push(std::make_shared<Event>(p->dist_supp_gamma(p->eng), 0, supplier, 0, nullptr));
    
    }

}

double System::obtainRR(double t){
    double ret = 0;
    for(int i = 0; i < p->S; i++){
        ret += (servers.at(i)->sellBuy - servers.at(i)->y)/t;
    }
    return ret;
}

int System::nextState(){
    simulation_time = events.top()->t;

#ifdef DEBUG
    std::cout << "simulation_time = " << simulation_time << std::endl;
#endif

    if(simulation_time > p->H){

#ifdef DEBUG
        std::cout << "end of simulation." << std::endl;
#endif

        return 1;
    }

    while(!events.empty()){
        if (simulation_time < events.top()->t){

#ifdef DEBUG
            std::cout << "no more events." << std::endl;
#endif

            break;
        }
        auto e = std::move(events.top());
#ifdef ALTERNATIVE
        std::cout << "\t(" << e->t << ", " << e->id << ", " << (e->p?e->p->id:-1) << ", " << e->code << ", {" << (e->m?e->m->sender->id:-1) << ", " << (e->m?e->m->t:-1) << ", " << (e->m?e->m->receiver:-1) << ", " << (e->m?e->m->upwards:false) << "{";
        if(e->m){
            for (int i = 0; i<e->m->args.size(); i++){
                std::cout << e->m->args.at(i) << ", ";
            }
        }
        std::cout << "}})" << std::endl;
        #endif
        events.pop();
        if(auto c = std::dynamic_pointer_cast<Customer>(e->p)){

            // customers
            if(e->m == nullptr){
                c->requestProduct(simulation_time);

                double next = e->t + p->dist_cust_tao(p->eng);
#ifdef DEBUG
                std::cout << "\tnext product request for customer " << c->id << " at time " << next << std::endl;
#endif
                events.push(std::make_shared<Event>(next, 0, c, 0, nullptr));
            }else{
#ifdef DEBUG
                std::cout << "\tCustomer " << c->id << " received (" << e->m->args.at(0) << ", " << e->m->args.at(1) << ", " << e->m->args.at(0) << ")" << std::endl;
#endif
                c->receiveMessage(e->m);
            }
        }else if(auto s = std::dynamic_pointer_cast<Server>(e->p)){
            // servers
            if(e->m == nullptr){
                if(e->id == 1){
#ifdef DEBUG
                std::cout << "\tServer " << s->id << " updating y = " << s->y << " -> ";
#endif
                    s->updateY();
#ifdef DEBUG
                std::cout << s->y << std::endl;
#endif
                    events.push(std::make_shared<Event>(simulation_time + p->T, 1, s, 0, nullptr));
                    continue;
                }
                s->requestProduct(simulation_time);
                if(s->id%2){

                    events.push(std::make_shared<Event>(e->t + p->ST1, 1, s, 0, nullptr));
#ifdef DEBUG
                    std::cout << "\tnext product request for server " << s->id << " at time " << e->t+p->ST1 << std::endl;
#endif
                }
                else{
                    events.push(std::make_shared<Event>(e->t + p->ST0, 1, s, 0, nullptr));
#ifdef DEBUG
                std::cout << "\tnext product request for server " << s->id << " at time " << e->t+p->ST0 << std::endl;
#endif
                }
            }else{
                s->receiveMessage(e->m);
            }
        }else if(auto db = std::dynamic_pointer_cast<DB>(e->p)){
            // DB
            db->receiveMessage(e->m);
        }else{
            // supplier
            auto sup = std::dynamic_pointer_cast<Supplier>(e->p);
            sup->sendSupply(e->t);
            double next = e->t + p->dist_supp_gamma(p->eng);
            events.push(std::make_shared<Event>(next, 0, sup, 0, nullptr));
#ifdef DEBUG
                std::cout << "\tnext product supply for supplier " << sup->id << " at time " << next << std::endl;
#endif        
        }
        
    }
    cust_serv->dequeue();
    serv_DB->dequeue();
    DB_sup->dequeue();
    return 0;

}