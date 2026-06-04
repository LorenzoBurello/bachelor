#include "supplier.hpp"

Supplier::Supplier(Params* p_init, Network* net_DB_sup_init, int id_init):
Peer(id_init)
{
    p = p_init;
    net_DB_sup = net_DB_sup_init;
}

void Supplier::receiveMessage(std::shared_ptr<Message> m)  {
}

void Supplier::sendMessage(){
    
}

void Supplier::sendSupply(double t){
    int product = p->dist_product(p->eng)-1;
    int quantity = p->dist_quantity(p->eng);
    net_DB_sup->p2n.push(std::make_unique<Message>(Message{this, t, 1, false, std::vector<int>{product, quantity}}));

#ifdef DEBUG
                std::cout << "supplier " << id << " sending (" << product << ", " << quantity << ") to DB " << std::endl;
#endif
}