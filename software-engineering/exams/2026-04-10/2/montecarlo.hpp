#pragma once
#include "params.hpp"
#include "simulator.hpp"

class Montecarlo{

public:

    Montecarlo(Params* p_init);
    void simulate();
    double getCollisionRate();

    Params* p;
    double avg = 0;
    
};
