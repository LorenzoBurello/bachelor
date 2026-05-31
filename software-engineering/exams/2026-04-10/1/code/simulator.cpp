#include "simulator.hpp"

Simulator::Simulator(Params* p_init)
{
    p = p_init;

}

void Simulator::init(){
    
    drones.reserve(p -> N);
    for(size_t _ = 0; _ < p->N; _++){
        drones.push_back(std::make_unique<MDP>(p));
    }
}