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
  * adc_hl() / ADC A,HL
  * Add the byte pointed to by the stack pointer HL plus the carry flag to A.
  */
//void gb::adc_hl(void);      //ADC A,HL

/*
 * add(uint8_t) / add a,r8
 * Add the value in register r8 to A.
 */
void gb::add(int reg8){      //ADD A,r8
    uint8_t source = getRegisters().getReg8(reg8);
    uint8_t dest = getRegisters().getReg8(A);
    uint8_t newValue = source + dest;

    //If the value is zero we can set the z flag.
    if(newValue) getRegisters().clearFlag(FLAG_Z);
    else getRegisters().setFlag(FLAG_Z);

    //If we carry the bit from the first nibble we need to set the half-carry flag.
    if(((source & 0x0f) + (dest & 0x0f)) > 0x0f) getRegisters().setFlag(FLAG_H);
    else getRegisters().clearFlag(FLAG_H);

    //If we carry the bit from the entire value, we need to set the carry flag.
    if((source + dest) > 0xff) getRegisters().setFlag(FLAG_C);
    else getRegisters().clearFlag(FLAG_C);

    //Always clear the N flag, because we are doing an add.
    getRegisters().clearFlag(FLAG_N);
    //Set new register value.
    getRegisters().setReg8(A, newValue);
}

/*
 * add_n(uint8_t) / ADD A,n8
 * Add the immediate value n8 to A.
 */
void gb::add_n(uint8_t value){    //ADD A,n8
    uint8_t dest = getRegisters().getReg8(A);
    uint8_t newValue = value + dest;

    //If the value is zero we can set the z flag.
    if(newValue) getRegisters().clearFlag(FLAG_Z);
    else getRegisters().setFlag(FLAG_Z);

    //If we carry the bit from the first nibble we need to set the half carry flag.
    if((value & 0x0f) + (dest & 0x0f) > 0x0f) getRegisters().setFlag(FLAG_H);
    else getRegisters().clearFlag(FLAG_H);

    //If we carry the bit from the entire value, we need to set the carry flag.
    if((value + dest) > 0xff) getRegisters().setFlag(FLAG_C);
    else getRegisters().clearFlag(FLAG_C);

    //Always clear flag N because we are doing an add.
    getRegisters().clearFlag(FLAG_N);
    //Set new register value.
    getRegisters().setReg8(A, newValue);
}

/*
 * add_hl() / ADD A,HL
 * Add the byte pointed to by HL to A.
 */
void gb::add_hl(){      //ADD A,HL
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source + dest;

  //If we carry the bit from the lower nibble, we need to set the half carry flag.
  if((source & 0x0f) + (dest & 0x0f) > 0x0f) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we carry the bit from the entire value, we need to set the carry flag.
  if((source + dest) > 0xff) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Always clear flag N because we are doing an add.
  getRegisters().clearFlag(FLAG_N);
  //Set new register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * add(uint16_t) / ADD HL,r16
 * Add the value in r16 to HL.
 */
void gb::add_r16(int reg){     //ADD HL,r16
    uint16_t source = getMemory().getWord(reg);
    uint16_t dest = getRegisters().getReg16(HL);
    uint16_t newValue = source + dest;

    //If the value is zero we can set the z flag.
    if(newValue) getRegisters().clearFlag(FLAG_Z);
    else getRegisters().setFlag(FLAG_Z);

    //If we carry the bit from the lower byte, set the h flag.
    if((source & 0x00ff) + (dest & 0x00ff) > 0x00ff) getRegisters().setFlag(FLAG_H);
    else getRegisters().clearFlag(FLAG_H);

    //If we carry the bit from the full add, set the c flag.
    if(source + dest > 0xffff) getRegisters().setFlag(FLAG_C);
    else getRegisters().clearFlag(FLAG_C);

    //Always clear flag N because we are doing an add.
    getRegisters().clearFlag(FLAG_N);
    //Set new register value.
    getRegisters().setReg16(HL, newValue);
}

/*void gb::op_and(uint8_t);   //AND A,r8
void gb::op_and_n(uint8_t); //AND A,n8
void gb::op_and_hl();       //AND A,HL
void gb::op_or(uint8_t);    //OR A,r8
void gb::op_or_n(uint8_t);  //OR A,n8
void gb::op_or_hl(void);    //OR A,HL
void gb::cp(uint8_t);       //CP A,r8
void gb::cp_n(uint8_t);     //CP A,n8
void gb::cp_hl(void);       //CP A,HL
void gb::dec(uint8_t);      //DEC r8
void gb::dec_hl(void);      //DEC HL
void gb::dec(uint16_t);     //DEC r16
void gb::inc(uint8_t);      //INC r8
void gb::inc_hl(void);      //INC HL
void gb::inc(uint16_t);     //INC r16
void gb::sbc(uint8_t);      //SBC A,r8
void gb::sbc_n(uint8_t);    //SBC A,n8
void gb::sbc_hl(void);      //SBC A,HL
void gb::sub(uint8_t);      //SUB A,r8
void gb::sub_n(uint8_t);    //SUB A,n8
void gb::sub(void);         //SUB A,HL
void gb::op_xor(uint8_t);   //XOR A,r8
void gb::op_xor_n(uint8_t); //XOR A,n8
void gb::op_xor_hl(void);   //XOR A,HL
*/

/*
 * update_flags(uint8_t) 
 * updates the flags based on a value passed in.
 */
void gb::update_flags(uint8_t value_src, uint8_t value_dst){
    return;
}