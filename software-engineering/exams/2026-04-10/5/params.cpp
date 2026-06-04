#include "params.hpp"

Params::Params():
    dist_even_product(0),
    dist_even_quantity(0),
    dist_even_server(0),
    dist_even_server_even_item(0),
    dist_odd_server_even_item(1),
    dist_even_server_even_quantity(0),
    dist_odd_server_even_quantity(1),
    dist_cost(1, 100)
{
    eng = pseudo_random_engine_from_device();
}

int Params::get_even(std::uniform_int_distribution<int>& dist){
    return dist(eng)*2;
}

int Params::get_odd(std::uniform_int_distribution<int>& dist){
    return dist(eng)*2 - 1;
}

void Params::init_distributions(){
    dist_product = std::uniform_int_distribution<>(1, P);
    dist_quantity = std::uniform_int_distribution<>(0, Q);

    dist_cust_tao = std::uniform_real_distribution<double>(A, B);
    dist_supp_gamma = std::uniform_real_distribution<double>(V, W);
    if(S != 1)
        dist_even_server = std::bernoulli_distribution(S0);
    
    dist_chose_even_server = std::uniform_int_distribution<int> (1, floor(S/2.0));
    dist_chose_odd_server = std::uniform_int_distribution<int> (1, ceil(S/2.0));
    if(P != 1){
        dist_even_product = std::bernoulli_distribution(P0);
        dist_even_server_even_item = std::bernoulli_distribution(SEP);
        dist_odd_server_even_item = std::bernoulli_distribution(1-SOP);
    }
        
    dist_chose_even_product = std::uniform_int_distribution<int> (1, floor(P/2.0));
    dist_chose_odd_product = std::uniform_int_distribution<int> (1, ceil(P/2.0));
    if(Q != 1){
        dist_even_quantity = std::bernoulli_distribution(Q0);
        dist_even_server_even_quantity = std::bernoulli_distribution(QEA);
        dist_odd_server_even_item = std::bernoulli_distribution(1-QOA);
    }
    
    dist_chose_even_quantity = std::uniform_int_distribution<int> (1, floor(Q/2.0));
    dist_chose_odd_quantity = std::uniform_int_distribution<int> (1, ceil(Q/2.0));

}