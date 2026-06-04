#include "simulator.hpp"

Simulator::Simulator(Params* p_init, System* simulation_system_init){
    p = p_init;
    simulation_system = simulation_system_init;
};

double Simulator::simulate(){
    simulation_system->init();
    while(!simulation_system->nextState())
        continue;
    
    return simulation_system->obtainRR(p->H);
}