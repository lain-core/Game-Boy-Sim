#ifndef GB_H
#define GB_H

#include <iostream>
#include <cstdint>
#include "Memory.h"
#include "Registers.h"

class gb{
    bool ime; //IME = Interrupt Master Enable
    bool status;
    int cycles;
    Memory          memory;
    Registers       regs;

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
        bool getStatus(){return status;}
        int getPC(){return pc;}
        int pc = 0x0100;

    /* Opcode-Related Functions */
    void decode(uint16_t);
    bool decode_misc(uint8_t, uint8_t);
    bool decode_math(uint8_t, uint8_t);
    bool decode_bitops(uint8_t, uint8_t);

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

    /* Arithmetic Opcodes */
    void adc(uint8_t);      //ADC A,r8
    void adc_n(uint8_t);    //ADC A,n8
    void adc_sp(void);      //ADC A,HL
    void add(uint8_t);      //ADD A,r8
    void add_n(uint8_t);    //ADD A,n8
    void add_sp(void);      //ADD A,HL
    void add(uint16_t);     //ADD HL,r16
    void op_and(uint8_t);   //AND A,r8
    void op_and_n(uint8_t); //AND A,n8
    void op_and_sp();       //AND A,HL
    void op_or(uint8_t);    //OR A,r8
    void op_or_n(uint8_t);  //OR A,n8
    void op_or_sp(void);    //OR A,HL
    void cp(uint8_t);       //CP A,r8
    void cp_n(uint8_t);     //CP A,n8
    void cp_sp(void);       //CP A,HL
    void dec(uint8_t);      //DEC r8
    void dec_sp(void);      //DEC HL
    void dec(uint16_t);     //DEC r16
    void inc(uint8_t);      //INC r8
    void inc_sp(void);      //INC HL
    void inc(uint16_t);     //INC r16
    void sbc(uint8_t);      //SBC A,r8
    void sbc_n(uint8_t);    //SBC A,n8
    void sbc_sp(void);      //SBC A,HL
    void sub(uint8_t);      //SUB A,r8
    void sub_n(uint8_t);    //SUB A,n8
    void sub(void);         //SUB A,HL
    void op_xor(uint8_t);   //XOR A,r8
    void op_xor_n(uint8_t); //XOR A,n8
    void op_xor_sp(void);   //XOR A,HL

    /* Bit Operations Opcodes */
    //Not to be confused with bit shifting.
    void bit(int);
    void res(int);
    void set(int);
    void swap(int);

    /* Debug-only Functions -- Clear for final build */
    void setStatus(bool newStatus){status = newStatus;}
};

#endif
