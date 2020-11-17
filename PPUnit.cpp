// PPUnit.cpp
// Authors: Hunter King, Joe Story

#include <iostream>
#include <iomanip>
#include "PPUnit.h" 

PPUnit::PPUnit(Memory arg_memory){
    memory = arg_memory;
}


/*
 * getRowColor
 * Given two bytes, returns a pointer to an array of 8 PPUnits on screen with their associated color value (0-3).
 * For example, the tile 0x5030 will return: [0, 1, 2, 3, 0, 0, 0, 0]
 */
uint8_t * PPUnit::getRowColor(uint16_t row){
    uint16_t byte1 = (row & 0xFF00) >> 8; // grab high order byte out of the 2
    uint16_t byte2 = (row & 0x00FF);      // grab low order byte
    uint16_t mask = 0x01;

    std::cout << "our tile is: 0x" << std::hex << row << std::endl;
    std::cout << "our byte1 is: 0x" << std::hex << byte1 << std::endl;
    std::cout << "our byte2 is: 0x" << std::hex << byte2 << std::endl;

    for (int i = 0; i < 8; i++){
            if (byte1 & (mask << i)) miniPix[7-i] += 1; // if byte 1's bit is on
            if (byte2 & (mask << i)) miniPix[7-i] += 2; // if byte 2's bit is on
    }
    
    return miniPix;
}

void PPUnit::render_tiles(){
// where to draw the visual area and the window
   uint8_t scrollY = memory.getByte(SCROLL_Y);
   uint8_t scrollX = memory.getByte(SCROLL_X);
   uint8_t windowY = memory.getByte(WINDOW_Y);
   uint8_t windowX = memory.getByte(WINDOW_X) - 7;
   printf("ScrollY: %02x\n", memory.getByte(SCROLL_Y));
}