#ifndef GB_H
#define GB_H

#include <iostream>
#include <cstdint>
#include <string>
#include "Memory.h"
#include "Registers.h"

class gb{
    int cycles;
    Memory          memory;
    Registers     regs;

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
            //void dumpProgRegisters();
            //void dumpProcRegisters();
            //void trace(void);
        Memory & getMemory(){return memory;}
        //Registers& getProgRegisters(){return regs;}
};

#endif
