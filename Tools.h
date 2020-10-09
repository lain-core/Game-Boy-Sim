/*
    File:   Tools.h
    Desc:   Declarations for utility functions used in
            Z80 simulator. Taken from CS 3481 Y86 Simulator Project.
*/
#ifndef TOOLS_H
#define TOOLS_H
#include <cstdint>

namespace Tools
{
    uint8_t bcd(uint8_t source);
    uint8_t getBits(unsigned low, unsigned high, uint8_t source);
    uint8_t setBits(unsigned low, unsigned high, uint8_t source);
    uint8_t clearBits(unsigned low, unsigned high, uint8_t source);
    uint8_t assignOneBit(unsigned bitNum, unsigned bitVal, uint8_t source);
    bool isNegative(uint8_t source);
    void clearBuffer(char *pbuf, int size);
} // namespace Tools

#endif
