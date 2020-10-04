#ifndef GB_H
#define GB_H

#include <iostream>
#include <cstdint>
#include "Memory.h"
#include "Registers.h"
#include "Pixel.h"

class gb{
    bool ime; //IME = Interrupt Master Enable/
    bool status;
    int cycles;
    Memory          memory;
    Registers       regs;
    Pixel           pix;

    /* Private Member Functions */

    //bool    readFile    (std::ifstream& infile);
    //int     writeMemory (std::string inst, uint16_t address);
    //void    getLine     (uint16_t *, uint16_t);
    //void    storeData   (uint16_t, int, std::string);
    //bool    readFile    (std::string);
    //std::string getFlagsString (void); //Defined in Trace.cpp

    /* Public Member Functions */
    public:
        gb();
        void reset();
        //void clock();
        //uint8_t getStat(void)
        bool load   (std::string);
        bool readFile(std::string);
        void trace(void);
        Memory & getMemory(){return memory;}
        Registers & getRegisters(){return regs;}
        Pixel & getPixel(){return pix;}
        bool getStatus(){return status;}
        int getPC(){return pc;}
        int pc = 0x0100;

    /* Opcode-Related Functions */
    void decode(uint8_t);
    bool decode_misc(uint8_t);

    /* Miscellaneous Opcodes */
    void ccf(void);
    void cpl(void);
    void daa(void);
    void di(void);
    void ei(void);
    void halt(void);
    void nop(void);
    void scf(void);
    void stop(void);

    /* Debug-only Functions -- Clear for final build */
    void setStatus(bool newStatus){status = newStatus;}
};

#endif
