#include "main.hpp"
int main(){


    // initialization
    Params p;
    InputReader ir(&p, "parameters.txt");
    OutputWriter ow("results.txt");
    Montecarlo m(&p);
    ir.obtainParams();

    p.init_distributions();
    m.simulate();
    ow.writeOutput(m.avg_RR);

    return EXIT_SUCCESS;
}