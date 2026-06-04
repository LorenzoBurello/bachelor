#include "customer.hpp"
#include "network.hpp"

Customer::Customer(Params* p_init, Network* cust_serv_init, int id_init):
    Peer(id_init)
{
    p = p_init;
    cust_serv = cust_serv_init;
    send_time = p->dist_cust_tao(p->eng);
}

void Customer::receiveMessage(std::shared_ptr<Message> m)  {

}
void Customer::sendMessage(){
    int server = 0;
    int product = 0;
    int quantity = 0;

    if(p->dist_even_server(p->eng))
        server = p->get_even(p->dist_chose_even_server);
    else
        server = p->get_odd(p->dist_chose_odd_server);
    
    if(p->dist_even_product(p->eng))
        product = p->get_even(p->dist_chose_even_product);
    else
        product = p->get_odd(p->dist_chose_odd_product);

    if(p->dist_even_quantity(p->eng))
        quantity = p->get_even(p->dist_chose_even_quantity);
    else
        quantity = p->get_odd(p->dist_chose_odd_quantity);
        
    cust_serv->p2n.push(std::make_unique<Message>(this, 0.0, server, true, std::vector<int>{product, quantity}));
}

void Customer::requestProduct(double t){
    int server = 0;
    int product = 0;
    int quantity = 0;

    if(p->dist_even_server(p->eng))
        server = p->get_even(p->dist_chose_even_server);
    else
        server = p->get_odd(p->dist_chose_odd_server);
    
    if(p->dist_even_product(p->eng))
        product = p->get_even(p->dist_chose_even_product);
    else
        product = p->get_odd(p->dist_chose_odd_product);

    if(p->dist_even_quantity(p->eng))
        quantity = p->get_even(p->dist_chose_even_quantity);
    else
        quantity = p->get_odd(p->dist_chose_odd_quantity);
#ifdef DEBUG
                std::cout << "Customer " << id << " asked for (" << product << ", " << quantity << ") to server " << server << std::endl;
#endif 
    cust_serv->p2n.push(std::make_unique<Message>(this, t, server, true, std::vector<int>{product, quantity}));
}