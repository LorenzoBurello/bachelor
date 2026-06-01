#include "simulator.hpp"

namespace{
    double pow2(double a){
            return a*a;
        }
}

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

void Simulator::updateCollisions(int drone){
    
    for (int i = drone-1; i >= 0; i--){
        double dist = sqrt(pow2(drones[drone]->x - drones[i]->x) + pow2(drones[drone]->y - drones[i]->y) + pow2(drones[drone]->z - drones[i]->z));
        if(dist <= p->D)
            collisions++;
    }
}

void Simulator::advanceState(){
    for (size_t i = 0; i < p->N; i++){
        drones[i]->next_state();
        updateCollisions(i);
    }
}
void Simulator::start(){
    for (size_t h = 0; h*p->T < p->H; h++){
        advanceState();
    }
}