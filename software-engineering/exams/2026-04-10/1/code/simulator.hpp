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

    Params* p;

    std::vector<std::unique_ptr<MDP>> drones;
};