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
    uint64_t getBits(unsigned low, unsigned high, uint64_t source);
    uint64_t setBits(unsigned low, unsigned high, uint64_t source);
    uint64_t clearBits(unsigned low, unsigned high, uint64_t source);

    uint64_t assignOneBit(unsigned bitNum, unsigned bitVal, uint64_t source);

    uint8_t getByteNumber(unsigned byteNum, uint64_t source);
    uint64_t putByteNumber(unsigned byteNum, unsigned char byteVal,
                           uint64_t source);
    uint64_t buildWord(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3,
                       unsigned char b4, unsigned char b5, unsigned char b6, unsigned char b7);
    bool isNegative(uint64_t source);
    void expandBits(uint64_t source, char bits[72]);
    void clearBuffer(char *pbuf, int size);
} // namespace Tools

#endif
