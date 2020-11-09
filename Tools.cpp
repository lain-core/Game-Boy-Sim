/*
    Utility functions (e.g., for bit/byte manipulations) used in Z80 Simulator.
    File:   Tools.cpp
    Desc:   Declarations for utility functions used in
            Z80 simulator. Taken from CS 3481 Y86 Simulator Project.
*/

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Tools.h"
#include "gb.h"
#include "Registers.h"

#define WORDBITS 8 // Number of bits in a word ("quad-word" in x86 parlance)
#define MAXBITNUM (WORDBITS - 1)
#define WORDBYTES (WORDBITS / 8)
#define MAXBYTENUM (WORDBYTES - 1)

namespace Tools
{

/*-----------------------------------------------------------------------------------------------
    bcd
    Corrects a value to Binary Coded Decimal. 
    A binary number 0x53 represents a decimal value 83. However, in BCD, this represents decimal
    value 53 directly. However, if a digit > 9 is expressed, E.G. 0x0A, we must correct it.
    Example:
    bcd(0x0A);
    will return the value:
    0x10;
------------------------------------------------------------------------------------------------*/
    uint8_t bcd(uint8_t value){
        if(value > 0x99){
            value += 0x60;
        }
        if((value & 0x0f) > 0x09){
            value += 0x06;
        }
        return value;
    }

/*-----------------------------------------------------------------------------------------------
    getBits
	Extracts bits 'low' to 'high' (inclusive) from 'source' and returns the result as
	an 64-bit integer. 
	Example:
	
	getBits(12,15,0x0123456789abcdef);
	
	would return the value:
	
	0x00000000000000c;
	
	(Bits 12-15 of the 64-bit word, counting from the right correspond to hex digit 'c' in the
	source word. Note that any number of bits from 1 to 64 could be specified depending on the values
	of 'low' and 'high'.
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
    uint8_t getBits(unsigned low, unsigned high, uint8_t source)
    {

        /* User assert to catch bad input--these functions only called by simulator */
        assert(high < WORDBITS && low <= high);

        return (source << (MAXBITNUM - high)) >> (MAXBITNUM - high + low);
    }
    /*-----------------------------------------------------------------------------------------------
    setBits
	Sets (to 1) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
    uint8_t setBits(unsigned low, unsigned high, uint8_t source)
    {
        assert(high < WORDBITS && low <= high);

        uint8_t x = (high == MAXBITNUM) ? -1 : (~(-1 << (high + 1)));
        uint8_t y = (-1UL << low);
        return source | (x & y);
    }
    /*-----------------------------------------------------------------------------------------------
    clearBits
	
	Clears (to 0) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
    uint8_t clearBits(unsigned low, unsigned high, uint8_t source)
    {
        assert(high < WORDBITS && low <= high);

        uint8_t x = (high == MAXBITNUM) ? -1 : (~(-1 << (high + 1)));
        uint8_t y = (-1UL << low);
        return source & ~(x & y);
    }

/*-----------------------------------------------------------------------------------------------
    assignOneBit
	Sets the bit number 'bitNum' to the binary value (0 or 1) specified by 'bitVal' in
	the source word and returns the resulting word.
	
	'bitNum' must be in the range 0 to 63 (inclusive) and 'bitVal' must be 0 or 1.
------------------------------------------------------------------------------------------------*/
    uint8_t assignOneBit(unsigned bitNum, unsigned bitVal, uint8_t source)
    {
        assert(bitNum < WORDBITS && (bitVal == 0 || bitVal == 1));
        uint8_t mask = (1UL << bitNum);
        return (bitVal) ? (source | mask) : (source & ~mask);
    }

/*-----------------------------------------------------------------------------------------------
    isNegative

	Returns true if the input parameter is negative when interpreted as a signed value.
------------------------------------------------------------------------------------------------*/
    bool isNegative(uint8_t source)
    {
        return (source >> 7); // This uses a cast to signed--lots of other ways to check
                                      // most sig bit for 1
    }

/*-----------------------------------------------------------------------------------------------
    clearBuffer
	Treats pbuf as a pointer to an array of 'size' bytes and clears them all to zero.
------------------------------------------------------------------------------------------------*/
    void clearBuffer(char *pbuf, int size)
    {
        assert(pbuf != NULL && size >= 0 && size <= INT32_MAX);

        for (int i = 0; i < size; i++)
            pbuf[i] = 0;
        return;
    }

/*------------------------------------------------------------------------------------------------
    changeEndian
    flips the endianness of a 16-bit value.
-------------------------------------------------------------------------------------------------*/
    uint16_t changeEndian(uint16_t value){
        uint16_t temp = (value & 0xFF00) >> 8;
        value = (value << 8) | temp;
        return value;
    }

} // namespace Tools
