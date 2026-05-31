#pragma once
#include "basic.hpp"
#include "params.hpp"
#include "cmath"

class MDP
{
public:
    MDP(Params* p);

    std::default_random_engine r;

    Params* p;
    double x = 0, y = 0, z = 0;
    double theta = 0, phi = 0;

    std::uniform_real_distribution<> dist_theta;
    std::uniform_real_distribution<> dist_phi;
    std::uniform_int_distribution<> dist_uw;

    void next_state();

    void update_angular_coefficients();

    void update_pos_x();
    void update_pos_y();
    void update_pos_z();
    
};
