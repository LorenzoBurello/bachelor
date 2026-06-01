#pragma once
#include <vector>
#include <memory>
#include "basic.hpp"
#include "params.hpp"
#include "mdp.hpp"

class Simulator{

public:

    Simulator(Params* p_init);
    void init();
    void start();
    void advanceState();
    void updateCollisions(int drone);

    Params* p;
    int collisions = 0;

    std::vector<std::unique_ptr<MDP>> drones;
};