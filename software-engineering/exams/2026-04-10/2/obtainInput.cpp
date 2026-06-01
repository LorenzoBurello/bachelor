#include "obtainInput.hpp"

InputReader::InputReader(Params* p_init, std::string filename_init){
    p = p_init;
    filename = filename_init;
}

void InputReader::obtainParams(){
    std::ifstream f(filename);
    if(!f)
        return;
    
    std::string line;
    while(std::getline(f, line)){
        sscanf(line.c_str(), "T %lf", &(p -> T));
        sscanf(line.c_str(), "H %lf", &(p -> H));
        sscanf(line.c_str(), "L %lf", &(p -> L));
        sscanf(line.c_str(), "V %lf", &(p -> V));
        sscanf(line.c_str(), "D %lf", &(p -> D));
        sscanf(line.c_str(), "N %d", &(p -> N));
        sscanf(line.c_str(), "M %d", &(p -> M));
        sscanf(line.c_str(), "r %lf", &(p->r));
        sscanf(line.c_str(), "a %lf", &(p -> a));
        sscanf(line.c_str(), "b %lf", &(p -> b));

    }
}