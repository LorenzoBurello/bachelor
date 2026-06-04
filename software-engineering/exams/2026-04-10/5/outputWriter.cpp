#include "outputWriter.hpp"

OutputWriter::OutputWriter(std::string filename_init){

    filename = filename_init;
}

void OutputWriter::writeOutput(double result, double SEP, double SOP, double QOA, double QEA){
    std::ofstream f(filename);

    f << SIGNATURE << std::endl;
    f << "RR " << result << std::endl;
    f << "SEP " << SEP << std:: endl;
    f << "SOP " << SOP << std::endl;
    f << "QEA " << QEA << std::endl;
    f << "QOA " << QOA;
}