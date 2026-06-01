#include "outputWriter.hpp"

OutputWriter::OutputWriter(std::string filename_init){

    filename = filename_init;
}

void OutputWriter::writeOutput(double result){
    std::ofstream f(filename);

    f << SIGNATURE << std::endl;
    f << "C " << result;
}