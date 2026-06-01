#include <iostream>
#include "main.hpp"

int main(){


    Params p;
    InputReader inp_read(&p, "parameters.txt");
    Montecarlo m(&p);
    OutputWriter ow("results.txt");

    inp_read.obtainParams();



    std::cout << "T: " << p.T << std::endl;
    std::cout << "H: " << p.H << std::endl;
    std::cout << "L: " << p.L << std::endl;
    std::cout << "V: " << p.V << std::endl;
    std::cout << "N: " << p.N << std::endl;
    std::cout << "M: " << p.M << std::endl;
    std::cout << "a: " << p.a << std::endl;
    std::cout << "b: " << p.b << std::endl;


    m.simulate();
    ow.writeOutput(m.getCollisionRate());


    return EXIT_SUCCESS;
}