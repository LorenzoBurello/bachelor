#include "obtainInput.hpp"

InputReader::InputReader(Params* p_init, std::string filename_init){
    p = p_init;
    filename = filename_init;
}

void InputReader::obtainParams(){
    std::ifstream f(filename);
    if(!f)
        return;
    
    std::string key;
    while(f >> key){

        if(key =="QOA") f >> (p -> QOA);
        if(key =="QEA") f >> (p -> QEA);
        if(key =="SOP") f >> (p -> SOP);
        if(key =="SEP") f >> (p -> SEP);
        if(key =="Q0") f >> (p -> Q0);
        if(key =="P0") f >> (p -> P0);
        if(key =="S0") f >> (p -> S0);
        if(key =="ST0") f >> (p -> ST0);
        if(key =="ST1") f >> (p -> ST1);
        if(key =="H") f >> (p -> H);
        if(key =="T") f >> (p -> T);
        if(key =="M") f >> (p -> M);
        if(key =="C") f >> (p -> C);
        if(key =="S") f >> (p -> S);
        if(key =="F") f >> (p -> F);
        if(key =="A") f >> (p -> A);
        if(key =="B") f >> (p -> B);
        if(key =="V") f >> (p -> V);
        if(key =="W") f >> (p -> W);
        if(key =="P") f >> (p -> P);
        if(key =="Q") f >> (p -> Q);
        if(key =="r") f >> (p -> r);
        if(key =="rt") f >> (p -> rt);
        if(key =="G") f >> (p -> G);
        
    }
}