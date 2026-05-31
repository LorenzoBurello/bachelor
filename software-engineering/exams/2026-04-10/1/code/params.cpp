#include "params.hpp"

Params::Params(){
    r = pseudo_random_engine_from_device();
}