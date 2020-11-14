// Pixel.cpp
// Authors: Hunter King, Joe Story

#include <iostream>
#include <iomanip>
#include "Pixel.h"

Pixel::Pixel(){
}

/*
 * getRowColor
 * Given two bytes, returns a pointer to an array of 8 pixels on screen with their associated color value (0-3).
 * For example, the tile 0x5030 will return: [0, 1, 2, 3, 0, 0, 0, 0]
 */
uint8_t * Pixel::getRowColor(uint16_t row){
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
