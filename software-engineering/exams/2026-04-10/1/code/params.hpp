#pragma once
#include "basic.hpp"

class Params
{

public:
    Params();

    std::default_random_engine eng;
    double T = 0, H = 0, L = 0, V = 0, D = 0, a = 0, b = 0;
    int N = 0, M = 0;

};