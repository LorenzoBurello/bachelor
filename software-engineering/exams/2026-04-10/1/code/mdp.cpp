#include "mdp.hpp"

MDP::MDP(Params* p_init)
    :
    dist_theta(0, M_PI),
    dist_phi(0,2 * M_PI),
    dist_uw(-1, 1)
{

    p = p_init;
    // initialization position
    std::uniform_real_distribution<> dist_init_pos(- (p->L), p->L);
    x = dist_init_pos(p->r);
    y = dist_init_pos(p->r);
    z = dist_init_pos(p->r);

    // initialization theta, phi
    std::uniform_real_distribution<> dist_init_theta(0, M_PI);
    std::uniform_real_distribution<> dist_init_phi(0, 2*M_PI);
    theta = dist_init_theta(p->r);
    phi = dist_init_phi(p->r);
}

void MDP::update_angular_coefficients(){

    // update theta and phi
    theta = theta + p->T * p->a * dist_uw(p->r);
    phi = phi + p->T * p->b * dist_uw(p->r);

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