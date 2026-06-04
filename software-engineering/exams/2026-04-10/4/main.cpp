#include "main.hpp"
int main(){


    // initialization
    Params p;
    InputReader ir(&p, "parameters.txt");
    OutputWriter ow("results.txt");
    Montecarlo m(&p);
    ir.obtainParams();

    p.init_distributions();
    std::array<double, 2>best_fits = m.search_best_fit();
    ow.writeOutput(m.max_RR, best_fits[0], best_fits[1]);

    return EXIT_SUCCESS;
}