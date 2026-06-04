#pragma once
#include <iostream>
#include <fstream>
#include <string>

class OutputWriter{

public:

    OutputWriter(std::string filename_init);

    std::string filename;

    void writeOutput(double result);
    const std::string SIGNATURE = "2026-04-10-Lorenzo-Burello-mat";
};