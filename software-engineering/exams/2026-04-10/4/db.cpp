#include "db.hpp"
#include "network.hpp"

DB::DB(Params* p_init, Network* net_serv_DB_init, Network* net_DB_sup_init):
    products_quantity(p_init->P),
    products_cost(p_init->P),
    Peer(0)
{
    
    p = p_init;
    net_serv_DB = net_serv_DB_init;
    net_DB_sup = net_DB_sup_init;


    for(int i = 0; i < p->P; i++){
        products_quantity.at(i) = p->dist_quantity(p->eng);
        products_cost.at(i) = p->dist_cost(p->eng);
    }
}

void DB::receiveMessage(std::shared_ptr<Message> m)  {
    if(m->upwards){
        // richiesta
        int product = m->args.at(0);
        int quantity = m->args.at(1);
        int cost = products_cost.at(product-1);

        if(products_quantity.at(product-1) < quantity)
            quantity = products_quantity.at(product-1);

        products_quantity.at(product-1) -= quantity;
#ifdef DEBUG
        std::cout << "DB received a request for (" << m->args.at(0) << ", " << m->args.at(1) << ") from server " << m->sender->id << std::endl;
#endif
        net_serv_DB->p2n.push(std::make_unique<Message>(this, m->t, m->sender->id, false, std::vector<int>{product, quantity, cost}));
#ifdef DEBUG
        std::cout << "sending (" << product << ", " << quantity << ", " << cost << ")" << std::endl;
#endif
    }else{

        products_quantity.at(m->args.at(0)) += m->args.at(1);
#ifdef DEBUG
        std::cout << "DB received (" << m->args.at(0) << ", " << m->args.at(1) << ") from supplier " << m->sender->id << std::endl;
#endif
    }
}
void DB::sendMessage(){

}