#pragma once
#include "params.hpp"
#include "simulator.hpp"

class Montecarlo{

public:

    Montecarlo(Params* p_init);
    double simulate();


    Params* p;
    double avg = 0;
    
};
