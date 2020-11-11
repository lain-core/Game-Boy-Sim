#include "../gb.h"

//ADD HL,SP
//ADD SP,e8
//DEC SP
//INC SP
//LD SP,n16
//LD [n16],SP
//LD HL,SP+e8
//LD SP,HL
//POP AF
//POP r16
//PUSH AF
//PUSH r16

/*
 * push(int) / PUSH r16
 * Push the value of r16 onto the stack.
 */
void gb::push(int reg16){
    uint16_t reg_value = getRegisters().getReg16(reg16);
    uint16_t stackptr = getRegisters().getReg16(SP);
    uint8_t high_val = (reg_value & 0xF0) >> 8;
    uint8_t low_val = (reg_value & 0x0F);
    stackptr--;
    getMemory().putByte(stackptr, high_val);
    stackptr--;
    getMemory().putByte(stackptr, low_val);
    getRegisters().setReg16(SP, stackptr);   
}

 /*
  * push(uint16_t) / NONE
  * Push the value n16 onto the stack.
  */
void gb::push(uint16_t value){
    uint16_t stackptr = getRegisters().getReg16(SP);
    uint8_t high_val = (value & 0xF0) >> 8;
    uint8_t low_val = (value & 0x0F);
    stackptr--;
    getMemory().putByte(stackptr, high_val);
    stackptr--;
    getMemory().putByte(stackptr, low_val);
    getRegisters().setReg16(SP, stackptr);
}