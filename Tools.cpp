/*
    Utility functions (e.g., for bit/byte manipulations) used in Z80 Simulator.
    File:   Tools.cpp
    Desc:   Declarations for utility functions used in
            Z80 simulator. Taken from CS 3481 Y86 Simulator Project.
*/

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cstdint>
#include "Tools.h"

#define WORDBITS 64 // Number of bits in a word ("quad-word" in x86 parlance)
#define MAXBITNUM (WORDBITS - 1)
#define WORDBYTES (WORDBITS / 8)
#define MAXBYTENUM (WORDBYTES - 1)

namespace Tools
{

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
    uint64_t getBits(unsigned low, unsigned high, uint64_t source)
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
    uint64_t setBits(unsigned low, unsigned high, uint64_t source)
    {
        assert(high < WORDBITS && low <= high);

        uint64_t x = (high == MAXBITNUM) ? -1UL : (~(-1UL << (high + 1)));
        uint64_t y = (-1UL << low);
        return source | (x & y);
    }
    /*-----------------------------------------------------------------------------------------------
    clearBits
	
	Clears (to 0) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
    uint64_t clearBits(unsigned low, unsigned high, uint64_t source)
    {
        assert(high < WORDBITS && low <= high);

        uint64_t x = (high == MAXBITNUM) ? -1UL : (~(-1UL << (high + 1)));
        uint64_t y = (-1UL << low);
        return source & ~(x & y);
    }

    /*-----------------------------------------------------------------------------------------------
    assignOneBit
	Sets the bit number 'bitNum' to the binary value (0 or 1) specified by 'bitVal' in
	the source word and returns the resulting word.
	
	'bitNum' must be in the range 0 to 63 (inclusive) and 'bitVal' must be 0 or 1.
------------------------------------------------------------------------------------------------*/
    uint64_t assignOneBit(unsigned bitNum, unsigned bitVal, uint64_t source)
    {
        assert(bitNum < WORDBITS && (bitVal == 0 || bitVal == 1));
        uint64_t mask = (1UL << bitNum);
        return (bitVal) ? (source | mask) : (source & ~mask);
    }

    /*-----------------------------------------------------------------------------------------------
    getByteNumber
	Returns the specified byte number from the source word.
	
	Example:
	getByteNumber(3,0x0011223344556677);
	
	will return the single byte value:
	
	0x44
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
    uint8_t getByteNumber(unsigned byteNum, uint64_t source)
    {
        assert(byteNum < WORDBYTES);
        uint64_t mask = (uint64_t)0xff << (byteNum * 8);

        return (source & mask) >> (byteNum * 8);
    }
    /*-----------------------------------------------------------------------------------------------
    putByteNumber
	Returns the source word after replacing the specified byte (byteNum) with a given 
	byte value (byteVal).
	
	Example:
	putByteNumber(3,0x00,0x0011223344556677);
	
	will return the value:
	
	0x0011223300556677
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
    uint64_t putByteNumber(unsigned byteNum, uint8_t byteVal, uint64_t source)
    {
        assert(byteNum < WORDBYTES);
        uint64_t mask = ~(0xFFUL << (byteNum * 8));
        source = (source & mask) | ((uint64_t)byteVal << (byteNum * 8));
        return source;
    }
    /*-----------------------------------------------------------------------------------------------
    buildWord
	
	Returns a 64 bit word consisting of the 8 parameter bytes, where b0 is the least significant
	and b7 is the most significant byte.
------------------------------------------------------------------------------------------------*/
    uint64_t buildWord(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3,
                       unsigned char b4, unsigned char b5, unsigned char b6, unsigned char b7)
    {
        union {
            unsigned char bytes[WORDBYTES];
            uint64_t qval;
        } u;
        u.bytes[0] = b0; // This function depends on 64-bit word size
        u.bytes[1] = b1;
        u.bytes[2] = b2;
        u.bytes[3] = b3;
        u.bytes[4] = b4;
        u.bytes[5] = b5;
        u.bytes[6] = b6;
        u.bytes[7] = b7;

        return u.qval;
    }
    /*-----------------------------------------------------------------------------------------------
    isNegative

	Returns true if the input parameter is negative when interpreted as a signed value.
------------------------------------------------------------------------------------------------*/
    bool isNegative(uint64_t source)
    {
        return ((int64_t)source < 0); // This uses a cast to signed--lots of other ways to check
                                      // most sig bit for 1
    }
    /*-----------------------------------------------------------------------------------------------
    expandBits
	
	Reads the source and converts it to a character string consisting of 72 bytes--71 characters
	followed by a '\0' character (string terminator).
	Example usage: 
		char buf[72];
		expandBits(0xAABBCCDDEE001122UL,buf);

		Will cause the following string to be written to the buf[] array (not including quotes):
	
	"10101010 10111011 11001100 11011101 11101110 00000000 00010001 00100010"
	
	Note the space after every group of 8 digits except the last. The last byte of
	the string is the '\0' byte, that is not printable but used to indicate the end
	of a C string.
------------------------------------------------------------------------------------------------*/
    void expandBits(uint64_t source, char *bits) // This function depends on 64-bit word size
    {
        assert(bits != NULL);

        uint64_t mask = 0x8000000000000000UL;
        char *p = bits;
        for (int i = 0; i < WORDBITS; i++)
        {
            if ((i > 0) && ((i & MAXBYTENUM) == 0)) // MAXBYTENUM is 7 for 64-bit words
                *p++ = ' ';

            *p++ = (mask & source) ? '1' : '0'; // increment of pointer comes after the write

            mask >>= 1; // OK because mask is unsigned (logical right shift)
        }
        bits[71] = '\0'; // 0 byte at end

        return;
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

} // namespace Tools
