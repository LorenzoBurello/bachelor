#include "mdp.hpp"

MDP::MDP(Params* p_init)
    :
    dist_theta(0, M_PI),
    dist_phi(0,2 * M_PI)
{

    p = p_init;
    // initialization position
    std::uniform_real_distribution<> dist_init_pos(- (p->L), p->L);
    x = dist_init_pos(p->eng);
    y = dist_init_pos(p->eng);
    z = dist_init_pos(p->eng);

    // initialization theta, phi
    std::uniform_real_distribution<> dist_init_theta(0, M_PI);
    std::uniform_real_distribution<> dist_init_phi(0, 2*M_PI);
    theta = dist_init_theta(p->eng);
    phi = dist_init_phi(p->eng);
}

std::array<double, 3> MDP::obtain_state_t_2(int u, int w){
    
    // update state in t+1
    std::array<double, 3> pos = {0, 0, 0};
    pos[0] = x + p->T * (p->V * sin(theta) * cos(phi));
    pos[1] = y + p->T * (p->V * sin(theta) * sin(phi));
    pos[2] = z + p->T * (p->V * cos(theta));

    double theta1 = theta + p->T * p->a * u;
    double phi1 = phi + p->T * p->b * w;

    // update state in t+2
    pos[0] = pos[0] + p->T * (p->V * sin(theta1) * cos(phi1));
    pos[1] = pos[1] + p->T * (p->V * sin(theta1) * sin(phi1));
    pos[2] = pos[2] + p->T * (p->V * cos(theta1));

    return pos;
}

void MDP::update_angular_coefficients(){

    // update theta and phi
    theta = theta + p->T * p->a * u;
    phi = phi + p->T * p->b * w;

}

void MDP::update_pos_x(){
    x = x + p->T * (p->V * sin(theta) * cos(phi));
}
void MDP::update_pos_y(){
    y = y + p->T * (p->V * sin(theta) * sin(phi));
}
void MDP::update_pos_z(){
    z = z + p->T * (p->V * cos(theta));
}



void MDP::next_state(){
    update_pos_x();
    update_pos_y();
    update_pos_z();
    update_angular_coefficients();
}