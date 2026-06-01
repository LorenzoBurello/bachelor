#include "montecarlo.hpp"

Montecarlo::Montecarlo(Params* p_init){
 
    p = p_init;
    
}

void Montecarlo::simulate(){
    for(size_t _ = 0; _<p->M; _++){
        Simulator sim(p);
        sim.init();
        sim.start();
        avg += (sim.collisions - avg)/p->M;
    }
}

double Montecarlo::getCollisionRate(){
    return avg/p->H;
}