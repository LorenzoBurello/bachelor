#include "server.hpp"

Server::Server(Params* p_init, Network* net_cust_ser_init, Network* net_ser_DB_init, int id_init):
    Peer(id_init)
{
    p = p_init;
    net_cust_ser = net_cust_ser_init;
    net_ser_DB = net_ser_DB_init;
    for (int _=0; _<p->P; _++){
        cache.push_back({0, 0});
    }
}

void Server::receiveMessage(std::shared_ptr<Message> m)  {
   if (m->upwards){
       // request from customer
       int product = m->args.at(0);
       int qty = m->args.at(1);
       int v = cache.at(product-1)[1];
       if (qty > cache.at(product-1)[0])
           qty = cache.at(product-1)[0];
       cache.at(product-1)[0] -= qty;
       sellBuy += v*qty;
#ifdef DEBUG
                std::cout << "server " << id << " received a request for (" << m->args.at(0) << ", " << m->args.at(1) << ") from customer " << m->sender->id << std::endl;
#endif
       net_cust_ser->p2n.push(std::make_unique<Message>(this, m->t+p->r, m->sender->id, false, std::vector<int>{product, qty, v}));
#ifdef DEBUG
                std::cout << "sending (" << product << ", " << qty << ", " << v << ")" << std::endl;
#endif
    }else{
        // response from DB
        int product = m->args.at(0);
        int quantity = m->args.at(1);
        int v = m->args.at(2);
        sellBuy -= quantity*v;
        int prev = cache.at(product-1).at(0);
        cache.at(product-1).at(1) = v*p->rt;
        cache.at(product-1).at(0) += quantity;
#ifdef DEBUG
                std::cout << "server " << id << " received (" << m->args.at(0) << ", " << m->args.at(1) << ", " << m->args.at(2) << ") from DB. Product " << product << ": " << prev << "->" << cache.at(product-1).at(0) << std::endl;
#endif
   }
}

void Server::request_DB(double t){
}

void Server::sendMessage(){

}

void Server::requestProduct(double t){
    int item = -1;
    int quantity = -1;
    if(even_item(p->eng))
        item = p->dist_chose_even_product(p->eng) * 2 - 1;
    else
        item = p->dist_chose_odd_product(p->eng) * 2;
    
    if(even_quantity(p->eng))
        quantity = p->dist_chose_even_quantity(p->eng) * 2 + 1;
    else
        quantity = p->dist_chose_odd_quantity(p->eng) * 2;

#ifdef DEBUG
                std::cout << "Server " << id << " asked for (" << item << ", " << quantity <<") to DB" << std::endl;
#endif
    net_ser_DB->p2n.push(std::make_unique<Message>(Message{this, t, 1, true, {item, quantity}}));
}

void Server::updateY(){
    for(int i = 0; i<p->P; i++){
        #ifdef ALTERNATIVE
        std::cout << "y = " << cache.at(i).at(0) << " * " << cache.at(i).at(1) << " * " << p->T << " * " << 0.1 << std::endl;
        #endif
        y += cache.at(i).at(0)*cache.at(i).at(1)*p->T*0.1;
    }
    /*
    for(int i = 0; i<p->P; i++){
        y += cache.at(i).at(0)*cache.at(i).at(1);
    }
    y*= p->T * 0.1;
    */
}