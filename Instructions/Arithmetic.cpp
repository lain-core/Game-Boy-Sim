#include "../Sim.h"
#include "../gb.h"
#include "../Tools.h"

 /*
  * adc(uint8_t) / ADC A,r8
  * Add the value in r8 plus the carry flag to A.
  */
//void gb::adc(uint8_t);      //ADC A,r8

 /*
 * adc_n(uint8_t) / ADC A,n8
 * Add the immediate value n8 plus the carry flag to A.
 */
//void gb::adc_n(uint8_t);    //ADC A,n8

 /* 
  * adc_sp() / ADC A,HL
  * Add the byte pointed to by the stack pointer HL plus the carry flag to A.
  */
//void gb::adc_sp(void);      //ADC A,HL

/*
 * add(uint8_t) / add a,r8
 * Add the value in register r8 to A.
 */
void gb::add(int reg8){      //ADD A,r8
    uint8_t newValue = getRegisters().getReg8(reg8) + getRegisters().getReg8(A);
    update_flags(newValue);
    getRegisters().clearFlag(FLAG_N);
    getRegisters().setReg8(A, newValue);
}

/*
 * add_n(uint8_t) / ADD A,n8
 * Add the immediate value n8 to A.
 * Flags modified: 
 */
void gb::add_n(uint8_t value){    //ADD A,n8
    uint8_t newValue = value + getRegisters().getReg8(A);
    update_flags(newValue);
    getRegisters().clearFlag(FLAG_N);
    getRegisters().setReg8(A, newValue);
}

/*
 * add_sp() / ADD A,HL
 * Add the byte pointed to by HL to A.
 */
void gb::add_sp(){      //ADD A,HL
  uint8_t newValue = getRegisters().getReg8(A) + getMemory().getByte(getRegisters().getReg16(HL));
  update_flags(newValue);
  getRegisters().clearFlag(FLAG_N);
  getRegisters().setReg8(A, newValue);
}

/*
 * add(uint16_t) / ADD HL,r16
 * Add the value in r16 to HL.
 */
void gb::add_r16(int reg){     //ADD HL,r16
    uint16_t newValue = getMemory().getWord(reg) + getRegisters().getReg16(HL);
    getRegisters().clearFlag(FLAG_N);
    //TODO: Make overflow right.
}

/*void gb::op_and(uint8_t);   //AND A,r8
void gb::op_and_n(uint8_t); //AND A,n8
void gb::op_and_sp();       //AND A,HL
void gb::op_or(uint8_t);    //OR A,r8
void gb::op_or_n(uint8_t);  //OR A,n8
void gb::op_or_sp(void);    //OR A,HL
void gb::cp(uint8_t);       //CP A,r8
void gb::cp_n(uint8_t);     //CP A,n8
void gb::cp_sp(void);       //CP A,HL
void gb::dec(uint8_t);      //DEC r8
void gb::dec_sp(void);      //DEC HL
void gb::dec(uint16_t);     //DEC r16
void gb::inc(uint8_t);      //INC r8
void gb::inc_sp(void);      //INC HL
void gb::inc(uint16_t);     //INC r16
void gb::sbc(uint8_t);      //SBC A,r8
void gb::sbc_n(uint8_t);    //SBC A,n8
void gb::sbc_sp(void);      //SBC A,HL
void gb::sub(uint8_t);      //SUB A,r8
void gb::sub_n(uint8_t);    //SUB A,n8
void gb::sub(void);         //SUB A,HL
void gb::op_xor(uint8_t);   //XOR A,r8
void gb::op_xor_n(uint8_t); //XOR A,n8
void gb::op_xor_sp(void);   //XOR A,HL
*/

/*
 * update_flags(uint8_t) 
 * updates the flags based on a value passed in.
 */
void gb::update_flags(uint8_t value){
  if(value) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);
  if((value & 0x0f) > 0x09) getRegisters().setFlag(FLAG_H);
  if(value > 0x99) getRegisters().setFlag(FLAG_C);
  
}