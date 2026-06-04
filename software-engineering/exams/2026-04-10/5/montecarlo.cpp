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

std::array<double, 4> Montecarlo::search_best_fit(){
    #ifdef CHECK_ST
                std::cout << "G = " << p->G << std::endl;
            #endif
    for(p->SOP = 0; p->SOP <= 1; p->SOP += (1.0/p->G)){
        for(p->SEP = 0; p->SEP <= 1; p->SEP += (1.0/p->G)){
            for(p->QOA = 0; p->QOA <= 1; p->QOA += (1.0/p->G)){
                for(p->QEA = 0; p->QEA <= 1; p->QEA += (1.0/p->G)){
                    #ifdef CHECK_ST
                            std::cout << "checking fit (" << p->SOP << ", " << p->SEP << ", " << p->QOA << ", " << p->QEA << ")" << std::endl;
                        #endif
                    simulate();
                    if (avg_RR > max_RR || first_cycle){
                        #ifdef CHECK_ST
                            std::cout << "found better fit, flushing last fits" << std::endl;
                        #endif
                        best_fits.clear();
                        max_RR = avg_RR;
                        first_cycle = false;
                    }
                    if (avg_RR >= max_RR){
                        #ifdef CHECK_ST
                            std::cout << "pushed fit (" << p->ST0 << ", " << p->ST1 << ")" << std::endl;
                        #endif
                        best_fits.push_back(std::array<double, 4>{p->SEP, p->SOP, p->QEA, p->QOA});
                    }
                    avg_RR = 0;

                }

            }

        }
    }
    std::uniform_int_distribution<> r(0, best_fits.size()-1);
    return best_fits.at(r(p->eng));
}