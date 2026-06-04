#pragma once

#include "params.hpp"
#include "system.hpp"

class Simulator{

    public:

    Simulator(Params* p_init, System* simulation_system_init);

    double simulate();

    Params* p;
    System* simulation_system;
};