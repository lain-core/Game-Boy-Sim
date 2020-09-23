// Memory.h
// Authors: Joe Story, Hunter King
#ifndef PIXEL_H
#define PIXEL_H 
#include <cstdint> //fixed-width unsigned ints

#include "Sim.h"

class Pixel{

    uint8_t miniPix[8] = {0};

public:
    Pixel();
    uint8_t* getTileColor(uint16_t);
};
#endif
