#include <iostream>

#include "../basic.hpp"

int main(){

    enum Light {RED = 0, YELLOW = 1, GREEN = 2};

    std::default_random_engine engine = pseudo_random_engine_from_device();
    std::uniform_int_distribution<> random_time(20, 60);
    Light traffic_light = Light::RED;

    size_t switch_time = random_time(engine);
    for (size_t time = 0; time < SIMULATION_HORIZON; time++){
        if(time < switch_time){
            continue;
        }
        switch_time = time + random_time(engine);
        switch (traffic_light)
        {
        case Light::RED :
            traffic_light = Light::YELLOW;
            break;
        case Light::YELLOW :
            traffic_light = Light::GREEN;
            break;
        default:
            traffic_light = Light::RED;
            break;
        }

        std::cout << "time: " << time << ", light: " << traffic_light << std::endl;
    }

    return EXIT_SUCCESS;
}