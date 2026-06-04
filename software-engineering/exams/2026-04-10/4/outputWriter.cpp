#include "outputWriter.hpp"

OutputWriter::OutputWriter(std::string filename_init){

    filename = filename_init;
}

void OutputWriter::writeOutput(double result, double ST0, double ST1){
    std::ofstream f(filename);

    f << SIGNATURE << std::endl;
    f << "RR " << result << std::endl;
    f << "ST0 " << ST0 << std:: endl;
    f << "ST1 " << ST1;
}