// Memory.h
// Authors: Joe Story, Hunter King
#ifndef PPUnit_H
#define PPUnit_H 
#include <cstdint> //fixed-width unsigned ints

#include "Sim.h"

class PPUnit{

    uint8_t miniPix[8] = {0};

public:
    PPUnit();
    uint8_t* getRowColor(uint16_t);
};
#endif
