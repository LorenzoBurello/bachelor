#include <iostream>

#include "../basic.hpp"

struct MarkovDecisionProcess{
    double states[2];
};

int main(){

    std::default_random_engine random_engine = pseudo_random_engine_from_device();
    std::uniform_real_distribution<> real_distribution(0, 1);
    std::vector<MarkovDecisionProcess> mdps = {2, {0.0, 0.0}};

        std::cout << "start: "
            << mdps[0].states[0] << ", "
            << mdps[0].states[1] << " -"
            << mdps[1].states[0] << ", "
            << mdps[1].states[1] << std::endl;

    for(size_t time = 0; time < 10; time++){
        double x1 = mdps[0].states[0];
        double x2 = mdps[0].states[1];

        mdps[0].states[0] = mdps[1].states[0]*real_distribution(random_engine);
        mdps[0].states[1] = mdps[1].states[1]*real_distribution(random_engine);

        mdps[1].states[0] = x1+real_distribution(random_engine);
        mdps[1].states[1] = x2+real_distribution(random_engine);

        std::cout << time << ": "
            << mdps[0].states[0] << ", "
            << mdps[0].states[1] << " - "
            << mdps[1].states[0] << ", "
            << mdps[1].states[1] << std::endl;
    }

    return EXIT_SUCCESS;
}