#pragma once
#include "params.hpp"
#include "simulator.hpp"

class Montecarlo{

public:

    Montecarlo(Params* p_init);
    void simulate();

    Params* p;
    double avg_RR = 0;
    
};