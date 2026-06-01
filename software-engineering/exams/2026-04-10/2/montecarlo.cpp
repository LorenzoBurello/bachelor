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
#ifdef DEBUG
        std::cout << "finished montecarlo n°" << _ << std::endl;
#endif
    }
}

double Montecarlo::getCollisionRate(){
    return avg/p->H;
}