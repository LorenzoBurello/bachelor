#include "network.hpp"
#include "system.hpp"

Message::Message(Peer* sender_init, double t_init, int receiver_init, bool upwards_init, const std::vector<int>& args_init):
    sender(sender_init),
    receiver(receiver_init),
    args(args_init),
    t(t_init),
    upwards(upwards_init)

{

}


Network::Network()
{

}

void Network::dequeue(){
    
    while(!p2n.empty()){
    
        auto m = p2n.front();
        p2n.pop();
        
        int receiver = m->receiver-1;
        
        if(m->upwards)
            receiver += limit;

#ifdef DEBUG
        std::cout << "\t\treceived request(";
        for(auto x: m->args) std:: cout << x << ",";
        std::cout <<"\b) - created event (" << m->t+sys->p->r << ", " << receiver << ", ptr, 1, {";
        for(auto x: m->args) std:: cout << x << ",";
        std::cout << "\b})" << std::endl;
#endif
        m->t += sys->p->r;
        sys->events.push(std::make_shared<Event>(m->t, receiver, processes.at(receiver), 1, m));
        
    }
}