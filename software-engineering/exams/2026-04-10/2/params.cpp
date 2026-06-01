#include "params.hpp"

Params::Params(){
    eng = pseudo_random_engine_from_device();
}