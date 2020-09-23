// Pixel.cpp
// Authors: Hunter King, Joe Story

#include <iostream>
#include <iomanip>
#include <array>
#include "Pixel.h"
#include "Tools.h"

Pixel::Pixel(){
}

uint8_t * Pixel::getTileColor(uint16_t tile){
    uint16_t byte1 = (tile & 0xFF00) >> 8; // grab high order byte out of the 2
    uint16_t byte2 = (tile & 0x00FF);        // grab low order byte
    uint16_t mask = 0x01;

    std::cout << "our tile is: 0x" << std::hex << tile << std::endl;
    std::cout << "our byte1 is: 0x" << std::hex << byte1 << std::endl;
    std::cout << "our byte2 is: 0x" << std::hex << byte2 << std::endl;

    for (int i = 0; i < 8; i++){
            if (byte1 & (mask << i)) miniPix[7-i] += 1; // if byte 1's bit is on
            if (byte2 & (mask << i)) miniPix[7-i] += 2; // if byte 2's bit is on
    }
    
    for (int i = 0; i < 8; i++){
        printf("%d ", miniPix[i]);
    }
    
    return miniPix;
}
