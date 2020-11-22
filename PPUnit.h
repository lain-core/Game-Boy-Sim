// Memory.h
// Authors: Joe Story, Hunter King
#ifndef PPUnit_H
#define PPUnit_H 
#include <cstdint> //fixed-width unsigned ints

#include "Sim.h"
#include "Memory.h"

class PPUnit{
    uint8_t miniPix[TILE_WIDTH] = {0};
    uint32_t lcdArray[LCD_WIDTH] = {0}; 
    Memory * memory;


public:
    void addMem(Memory *);
    uint32_t *getRowColor(uint16_t);
    void render_tiles();
    void scan_line();
    }; //End class PPUnit
#endif
