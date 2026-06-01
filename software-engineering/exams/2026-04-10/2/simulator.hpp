#pragma once
#include <vector>
#include <memory>
#include "array"
#include "basic.hpp"
#include "params.hpp"
#include "mdp.hpp"

class Simulator{

public:

    Simulator(Params* p_init);
    void init();
    void start();
    void advanceState();
    void detectAndAvoidCollisions();
    double getDistanceBetweenDrones(size_t i, size_t j);
    double simulateDistanceWithOptions(size_t i, std::vector<int> near_drones, int u, int w);

    Params* p;
    int collisions = 0;

    std::vector<std::unique_ptr<MDP>> drones;
};