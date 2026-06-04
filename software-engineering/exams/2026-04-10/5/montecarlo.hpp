#pragma once
#include "params.hpp"
#include "simulator.hpp"

#include <vector>

class Montecarlo{

public:

    Montecarlo(Params* p_init);
    void simulate();
    std::array<double, 4> search_best_fit();

    Params* p;
    double avg_RR = 0;
    
    bool first_cycle = true;
    double max_RR = 0;
    std::vector<std::array<double, 4>> best_fits;
};