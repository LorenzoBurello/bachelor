#pragma once
#include "basic.hpp"
#include "params.hpp"
#include "cmath"
#include "vector"
#include "array"

class MDP
{
public:
    MDP(Params* p);

    std::default_random_engine r;

    Params* p;
    double x = 0, y = 0, z = 0;
    double theta = 0, phi = 0;
    int u = 0, w = 0;
    
    std::uniform_real_distribution<> dist_theta;
    std::uniform_real_distribution<> dist_phi;
    
    void next_state();

    std::array<double, 3> obtain_state_t_2(int u, int w);

    void update_angular_coefficients();
    
    
    void update_pos_x();
    void update_pos_y();
    void update_pos_z();
    
};
