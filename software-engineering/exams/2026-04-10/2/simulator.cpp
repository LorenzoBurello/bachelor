#include "simulator.hpp"

namespace{
    double pow2(double a){
            return a*a;
        }
}

Simulator::Simulator(Params* p_init)
{
    p = p_init;

}

void Simulator::init(){
    
    drones.reserve(p -> N);
    for(size_t _ = 0; _ < p->N; _++){
        drones.push_back(std::make_unique<MDP>(p));
    }
}

void Simulator::advanceState(){
    for (size_t i = 0; i < p->N; i++){
        drones[i]->next_state();
    }
}

double Simulator::simulateDistanceWithOptions(size_t i, std::vector<int> near_drones, int u, int w){
#ifdef DEBUG
        std::cout << "\t(u, w) = (" << u << ", " << w << ")" << std::endl;         
#endif
    double minDist = (p->L) * sqrt(3);

    std::array<double, 3> t2Pos = drones.at(i)->obtain_state_t_2(u, w);
    for (int j = 0; j < near_drones.size(); j++){
        double d = sqrt(pow2(t2Pos.at(0) - drones[near_drones.at(j)]->x) + pow2(t2Pos.at(1) - drones[near_drones.at(j)]->y) + pow2(t2Pos.at(2) - drones[near_drones.at(j)]->z));
        if (d < minDist){
            minDist = d;
        }
#ifdef DEBUG
        std::cout << "\t\tdistance(" << i << ", " << near_drones.at(j) << ") = " << d << std::endl;         
#endif
    }
#ifdef DEBUG
        std::cout << "\t returning minDist = "<< minDist << std::endl;         
#endif
    return minDist;
}

double Simulator::getDistanceBetweenDrones(size_t i, size_t j){
    return sqrt(pow2(drones[i]->x - drones[j]->x) + pow2(drones[i]->y - drones[j]->y) + pow2(drones[i]->z - drones[j]->z));
}

void Simulator::detectAndAvoidCollisions(){
    for(size_t i = 0; i < p->N; i++){
        std::vector<int> near_drones;
        for(size_t j = 0; j < p->N; j++){
            if(i==j)
                continue;
            double distance = getDistanceBetweenDrones(i, j);
            if (distance <= p->r)
                near_drones.push_back(j);
            if(i<j){
                if(distance <= p->D)
                    collisions++;
            }
        }
        std::vector<int> minU;
        std::vector<int> minW;
        double bestDist = 0;
        double localMinDist = 0;
#ifdef DEBUG
        std::cout << "check best for drone " << i  << std::endl;         
#endif
        for(int u = -1; u <= 1; u++){
            for(int w = -1; w <= 1; w++){
                localMinDist = simulateDistanceWithOptions(i, near_drones, u, w);
                if (localMinDist > bestDist){
                    bestDist = localMinDist;
                    minU.clear();
                    minW.clear();
#ifdef DEBUG
        std::cout << "\tcleared best fits for drone " << i  << ". found "<< localMinDist << " < " << minDist << std::endl;         
#endif
                }
                if (localMinDist >= bestDist){
                    minU.push_back(u);
                    minW.push_back(w);
                }
            }

        }
        
        std::uniform_int_distribution<> distr(0, minU.size()-1);
        int index = distr(p->eng);
        drones[i]->u = minU[index];
        drones[i]->w = minW[index];
#ifdef DEBUG
        std::cout << "chosen best for drone " << i << ": (u, w) = (" << minU[index] << ", " << minW[index] << ")"  << std::endl;         
#endif
    }
}

void Simulator::start(){
    for (size_t h = 0; h*p->T < p->H; h++){
        detectAndAvoidCollisions();
        advanceState();
    }
}