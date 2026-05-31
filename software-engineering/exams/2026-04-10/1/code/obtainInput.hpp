#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "params.hpp"

class InputReader
{
public:
    InputReader(Params* p_init, std::string filename_init);

    void obtainParams();

    Params* p;
    std::string filename;
};

