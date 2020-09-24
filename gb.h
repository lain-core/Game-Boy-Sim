#ifndef GB_H
#define GB_H

#include <iostream>
#include <cstdint>
#include "Memory.h"
#include "Registers.h"
#include "Pixel.h"

class gb{
    bool status;
    int cycles;
    int pc;
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
        void decode(void);
        void trace(void);
        Memory & getMemory(){return memory;}
        Registers & getRegisters(){return regs;}
        Pixel & getPixel(){return pix;}

    /* Opcode-Related Functions */
    
    /* Miscellaneous Opcodes */
    void stop(void);
    void halt(void);
    void nop(void);
    void scf(void);
    void ccf(void);

};

#endif
