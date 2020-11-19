// Memory.h
// Authors: Joe Story, Hunter King
#ifndef PPUnit_H
#define PPUnit_H 
#include <cstdint> //fixed-width unsigned ints

#include "Sim.h"
#include "Memory.h"

class PPUnit{
    uint8_t miniPix[8] = {0};
    Memory * memory;


public:
    void addMem(Memory *);
    uint8_t *getRowColor(uint16_t);
    void render_tiles();
}; //End class PPUnit
#endif
