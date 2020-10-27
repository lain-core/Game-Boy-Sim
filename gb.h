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
        void sigint_handler(int);
        Memory & getMemory(){return memory;}
        Registers & getRegisters(){return regs;}
        bool getStatus(){return status;}
        void setStatus(bool newStatus){status = newStatus;}
        int getPC(){return pc;}
        int pc = 0x0000;

    /* Decode-Related Functions */
    bool decode(uint16_t);
    bool decode_misc(uint8_t, uint8_t);
    bool decode_math(uint8_t, uint8_t);
    bool decode_bitops(uint8_t, uint8_t);

    /* Decode Math Helpers */
    bool decode_add(uint8_t, uint8_t);
    bool decode_sub(uint8_t, uint8_t);
    bool decode_and_xor(uint8_t, uint8_t);
    bool decode_or_cp(uint8_t, uint8_t);
    bool decode_bit(uint8_t);
    bool decode_res(uint8_t);
    bool decode_set(uint8_t);
    int get_bitnum(uint8_t);
    int get_regnum(uint8_t);

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
    void adc(int);          //ADC A,r8
    void adc_n(uint8_t);    //ADC A,n8
    void adc_hl(void);      //ADC A,HL
    void add(int);          //ADD A,r8
    void add_n(uint8_t);    //ADD A,n8
    void add_hl(void);      //ADD A,HL
    void add_r16(int);      //ADD HL,r16
    void op_and(int);       //AND A,r8
    void op_and_n(uint8_t); //AND A,n8
    void op_and_hl();       //AND A,HL
    void op_or(int);        //OR A,r8
    void op_or_n(uint8_t);  //OR A,n8
    void op_or_hl(void);    //OR A,HL
    void cp(int);           //CP A,r8
    void cp_n(uint8_t);     //CP A,n8
    void cp_hl(void);       //CP A,HL
    void dec(int);          //DEC r8
    void dec_hl(void);      //DEC HL
    void dec_r16(int);      //DEC r16
    void inc(int);          //INC r8
    void inc_hl(void);      //INC HL
    void inc_r16(int);      //INC r16
    void sbc(int);          //SBC A,r8
    void sbc_n(uint8_t);    //SBC A,n8
    void sbc_hl(void);      //SBC A,HL
    void sub(int);          //SUB A,r8
    void sub_n(uint8_t);    //SUB A,n8
    void sub_hl(void);      //SUB A,HL
    void op_xor(int);       //XOR A,r8
    void op_xor_n(uint8_t); //XOR A,n8
    void op_xor_hl(void);   //XOR A,HL

    /* Arithmetic Opcode Helpers */
    void update_on_add(uint8_t, uint8_t); //Updates flags for ADD funcs.

    /* Load Opcode Helpers */
    void gb::ld(int, int);
    void gb::ld_n(int, uint8_t);
    void gb::ld_r16(int, uint16_t);
    void gb::ld_hlr(int);
    void gb::ld_hln(uint8_t);
    void gb::ld_rhl(int);
    void gb::ld_r16A(int);
    void gb::ld_n16A(uint16_t);
    void gb::ldh_n16A(uint16_t);
    
    /* Bit Operations Opcodes */
    //Not to be confused with bit shifting.
    void bit(int, int); //BIT u3,r8
    void bit_hl(int);   //BIT u3,[HL]
    void res(int, int); //RES u3,r8
    void res_hl(int);   //RES u3,[HL]
    void set(int, int); //SET u3,r8
    void set_hl(int);   //SET u3,[HL]
    void swap(int);     //SWAP r8
    void swap_hl(void); //SWAP [HL]
};

#endif
