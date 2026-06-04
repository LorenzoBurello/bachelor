#pragma once
#include <random>

#include "basic.hpp"

class Params{

public:
    Params();

    void init_distributions();

    int get_even(std::uniform_int_distribution<int>& dist);
    int get_odd(std::uniform_int_distribution<int>& dist);
    
    std::default_random_engine eng;
    // simulation horyzon
    double H = 0;
    
    double T = 0, rt = 0;
    double A = 0, B = 0, V = 0, W = 0, r = 0, S0 = 0, P0 = 0, Q0 = 0, ST0 = 0, ST1 = 0, SEP = 0, SOP = 0, QEA = 0, QOA = 0;
    int M = 0, C = 0, S = 0, F = 0, P = 0, Q = 0;

    std::uniform_real_distribution<> dist_cust_tao;
    std::uniform_real_distribution<> dist_supp_gamma;

    std::uniform_int_distribution<> dist_product;
    std::uniform_int_distribution<> dist_quantity;
    std::uniform_int_distribution<> dist_cost;

    std::bernoulli_distribution dist_even_server;
    std::uniform_int_distribution<> dist_chose_even_server;
    std::uniform_int_distribution<> dist_chose_odd_server;
    std::bernoulli_distribution dist_even_product;
    std::uniform_int_distribution<> dist_chose_even_product;
    std::uniform_int_distribution<> dist_chose_odd_product;
    std::bernoulli_distribution dist_even_quantity;
    std::uniform_int_distribution<> dist_chose_even_quantity;
    std::uniform_int_distribution<> dist_chose_odd_quantity;

    std::bernoulli_distribution dist_even_server_even_item;
    std::bernoulli_distribution dist_odd_server_even_item;

    std::bernoulli_distribution dist_even_server_even_quantity;
    std::bernoulli_distribution dist_odd_server_even_quantity;
    
};