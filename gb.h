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
    //GB RST vectors.
    uint8_t vectors[8] = {0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38};

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
    bool decode(uint8_t);
    bool decode_misc(uint8_t);
    bool decode_math(uint8_t);
    bool decode_load(uint8_t);
    bool decode_bitops(uint8_t);
    bool decode_stackops(uint8_t);
    bool decode_jump(uint8_t);
    uint8_t getData(void);
    uint16_t getWordData(void);

    /* Decode Math Helpers */
    bool decode_add(uint8_t);
    bool decode_sub(uint8_t);
    bool decode_and_xor(uint8_t);
    bool decode_or_cp(uint8_t);
    bool decode_bit(uint8_t);
    bool decode_res(uint8_t);
    bool decode_set(uint8_t);
    int get_bitnum(uint8_t);
    int get_regnum(uint8_t);


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

    /* Bit Operations Opcodes */
    //Not to be confused with bit shifting.
    void bit(int, int);     //BIT u3,r8
    void bit_hl(int);       //BIT u3,[HL]
    void res(int, int);     //RES u3,r8
    void res_hl(int);       //RES u3,[HL]
    void set(int, int);     //SET u3,r8
    void set_hl(int);       //SET u3,[HL]
    void swap(int);         //SWAP r8
    void swap_hl(void);     //SWAP [HL]
    
    /* Bit Shift Opcodes */
    void rl(int);           //RL r8
    void rl_hl(void);       //RL [HL]
    void rla(void);         //RLA
    void rlc(int);          //RLC r8
    void rlc_hl(void);      //RLC [HL]
    void rlca(void);        //RLCA
    void rr(int);           //RR r8
    void rr_hl();           //RR [HL]
    void rra(void);         //RRA
    void rrc(int);          //RRC r8
    void rrc_hl(void);      //RRC [HL]
    void rrca(void);        //RRCA
    void sla(int);          //SLA r8
    void sla_hl(void);      //SLA [HL]
    void sra(int);          //SRA r8
    void sra_hl();          //SRA [HL]
    void srl(int);          //SRL r8
    void srl_hl(void);      //SRL [HL]

    /* Load Opcodes */
    void ld(int, int);              //LD r8,r8
    void ld_n(int, uint8_t);        //LD r8,n8
    void ld_r16(int, uint16_t);     //LD r16,n16
    void ld_hl(int);               //LD [HL], r8
    void ld_hln(uint8_t);           //LD [HL], n8
    void ld_hl_r8(int);               //LD r8, [HL]
    void ld_r16A(int);              //LD [r16], A
    void ld_n16A(uint16_t);         //LD [n16], A
    void ldh_n16A(uint8_t);        //LDH [n16], A
    void ldh_c();            //LDH [C], A
    void ldh_c_a();          //LDH A,[C]
    void ld_a_r16(int);               //LD A,[r16]
    void ld_n16(uint16_t);          //LD A,[n16]
    void ldh_n16(uint8_t);         //LDH A,[n16]
    void ld_hli(void);              //LD [HLI],A
    void ld_hld(void);              //LD [HLD],A
    void ld_hld_a(void);            //LD A,[HLD]
    void ld_hli_a(void);            //LD A,[HLI]

    /* Jump Opcodes */
    void call(uint16_t);            //CALL n16
    void call_cc(bool, uint16_t);   //CALL cc,n16 
    void jp_hl(void);               //JP HL
    void jp(uint16_t);              //JP n16
    void jp_cc(bool, uint16_t);     //JP cc,n16
    void jr(int8_t);               //JR e8
    void jr_cc(bool, int8_t);      //JR cc,e8
    void ret_cc(bool);              //RET cc
    void ret(void);                 //RET
    void reti(void);                //RETI
    void rst(uint8_t);              //RST vec

    /* Stack Opcodes */
    void add_hl_sp(void);    //ADD HL,SP
    void add_sp_e8(uint8_t); //ADD SP,e8
    void dec_sp(void);       //DEC SP
    void inc_sp(void);       //INC SP
    void ld_sp(uint16_t);    //LD SP,n16
    void ld_n_sp(uint16_t);  //LD [n16], SP
    void ld_hl_e8(uint8_t);  //LD HL,SP+e8
    void ld_sp_hl(void);     //LD SP,HL
    void pop(void);          //POP AF
    void pop(int);           //POP r16
    void push(void);         //PUSH AF
    void push(int);          //PUSH r16
    

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

    /* Opcode Helpers */
    void update_on_add(uint8_t, uint8_t); //Updates flags for ADD funcs.
    void push_val(uint16_t); //Pushes a value onto the stack. NOT an opcode.

};

#endif
