#include "montecarlo.hpp"
#include <iostream>

Montecarlo::Montecarlo(Params* p_init){
 
    p = p_init;
    
}

void Montecarlo::simulate(){
    for(int _ = 0; _ < p->M; _++){
        System sys(p);
        Simulator sim(p, &sys);
        avg_RR += (sim.simulate()-avg_RR)/p->M;
        #ifdef ALTERNATIVE
        std::cout << avg_RR << std::endl;
        #endif
    }
}