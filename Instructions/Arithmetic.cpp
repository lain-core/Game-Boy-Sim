#include "../Sim.h"
#include "../gb.h"
//TODO: Cleanup. A lot of these functions use redundant logic, and I can really pare this file down if I clean it up a little and make some helper functions.

 /*
  * adc(uint8_t) / ADC A,r8
  * Add the value in r8 plus the carry flag to A.
  */
void gb::adc(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source + dest + getRegisters().getFlag(FLAG_C);

  //If the value is zero, set the zero flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If the bit is carried from the first nibble, set the h flag.
  if((source & 0x0f) + (dest & 0x0f) > 0x0f) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If the bit is carried from the whole byte, set the c flag.
  if(source + dest > 0xff) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Always clear flag N because we are doing an add.
  getRegisters().clearFlag(FLAG_N);
  //Set the register value.
  getRegisters().setReg8(A, newValue); 
}

 /*
 * adc_n(uint8_t) / ADC A,n8
 * Add the immediate value n8 plus the carry flag to A.
 */
void gb::adc_n(uint8_t value){
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = value + dest + getRegisters().getFlag(FLAG_C);

  //If the value is zero, set the zero flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If the bit is carried from the first nibble, set the h flag.
  if((value & 0x0f) + (dest & 0x0f) > 0x0f) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If the bit is carried from the whole byte, set the c flag.
  if(value + dest > 0xff) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Always clear flag N because we are doing an add.
  getRegisters().clearFlag(FLAG_N);
  //Set the register value.
  getRegisters().setReg8(A, newValue); 
}

 /* 
  * adc_hl() / ADC A,[HL]
  * Add the byte pointed to by HL plus the carry flag to A.
  */
void gb::adc_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source + dest + getRegisters().getFlag(FLAG_C);

  //If the value is zero, set the zero flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If the bit is carried from the first nibble, set the h flag.
  if((source & 0x0f) + (dest & 0x0f) > 0x0f) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If the bit is carried from the whole byte, set the c flag.
  if(source + dest > 0xff) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Always clear flag N because we are doing an add.
  getRegisters().clearFlag(FLAG_N);
  //Set the register value.
  getRegisters().setReg8(A, newValue); 
}

/*
 * add(uint8_t) / ADD A,r8
 * Add the value in register r8 to A.
 */
void gb::add(int reg8){
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
void gb::add_n(uint8_t value){
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
 * add_hl() / ADD A,[HL]
 * Add the byte pointed to by HL to A.
 */
void gb::add_hl(){
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
void gb::add_r16(int reg){
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

/*
 * op_and(int) / AND A,r8
 * Bitwise AND the value in r8 and A.
 */
void gb::op_and(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source & dest;

  //If the new value is zero, set the flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For AND, always set: Flag N: 0, Flag H: 1, Flag C: 0
  getRegisters().clearFlag(FLAG_N);
  getRegisters().setFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  //Set our register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * op_and_n / AND A,n8
 * Bitwise AND the value n8 and A.
 */
void gb::op_and_n(uint8_t value){
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = value & dest;

  //If the new value is zero, set the flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For AND, always set: Flag N: 0, Flag H: 1, Flag C: 0
  getRegisters().clearFlag(FLAG_N);
  getRegisters().setFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  //Set our register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * op_and_hl() / AND A,[HL]
 * Bitwise AND the value of the byte pointed to by HL and A.
 */
void gb::op_and_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source & dest;

  //If the new value is zero, set the flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For AND, always set: Flag N: 0, Flag H: 1, Flag C: 0
  getRegisters().clearFlag(FLAG_N);
  getRegisters().setFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  //Set our register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * op_or(int) / OR A,r8
 * Bitwise OR the value in r8 with A.
 */
void gb::op_or(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source | dest;

  //If the value is zero, set the Z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For OR, always set: Flag N: 0, Flag H: 0, Flag C: 0.
  getRegisters().clearFlag(FLAG_N);
  getRegisters().clearFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  getRegisters().setReg8(A, newValue);
}

/*
 * op_or_n(uint8_t) / OR A,n8
 * Bitwise OR the value n8 with A.
 */
void gb::op_or_n(uint8_t value){
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = value | dest;

  //If the value is zero, set the Z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For OR, always set: Flag N: 0, Flag H: 0, Flag C: 0.
  getRegisters().clearFlag(FLAG_N);
  getRegisters().clearFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  getRegisters().setReg8(A, newValue);
}

/*
 * op_or_hl() / OR A,[HL]
 * Bitwise OR the value in the byte pointed to by HL with A.
 */
void gb::op_or_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source | dest;

  //If the value is zero, set the Z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For OR, always set: Flag N: 0, Flag H: 0, Flag C: 0.
  getRegisters().clearFlag(FLAG_N);
  getRegisters().clearFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  getRegisters().setReg8(A, newValue);
}

/*
 * cp(int) / CP A,r8
 * ComPare the value in r8 to A, and set the flags, but don't store it.
 */
void gb::cp(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - source;

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow bit 4, we need to set the H flag.
  if((source & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the c flag (i.e. if r8 > A), set the C Flag.
  if(source > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set the N flag.
  getRegisters().setFlag(FLAG_N);
}

/*
 * cp_n(uint8_t) / CP A,n8
 * ComPare the value n8 to A, and set the flags, but don't store it.
 */
void gb::cp_n(uint8_t value){
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - value;

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow bit 4, we need to set the H flag.
  if((value & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the c flag (i.e. if r8 > A), set the C Flag.
  if(value > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set the N flag.
  getRegisters().setFlag(FLAG_N);
}

/*
 * cp_hl() / CP A,[HL]
 * ComPare the value in the byte pointed to by HL to A, and set the flags, but don't store it.
 */
void gb::cp_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - source;

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow bit 4, we need to set the H flag.
  if((source & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the c flag (i.e. if r8 > A), set the C Flag.
  if(source > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set the N flag.
  getRegisters().setFlag(FLAG_N);
}

/*
 * dec(int) / DEC r8
 * Decrement the value in r8.
 */
void gb::dec(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t newValue = source - 1;

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow bit 4, we need to set the H flag.
  if( ((source & 0x0f) >> 3) !=  ((newValue & 0x0f) >> 3) ) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //Since we are doing a subtract, always set the N flag.
  getRegisters().setFlag(FLAG_N);

  //Set the register value.
  getRegisters().setReg8(reg8, newValue);
}

/*
 * dec_hl() / DEC [HL]
 * Decrement the byte pointed to by HL by 1.
 */
void gb::dec_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t newValue = source - 1;

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow bit 4, we need to set the H flag.
  if( ((source & 0x0f) >> 3) !=  ((newValue & 0x0f) >> 3) ) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //Since we are doing a subtract, always set the N flag.
  getRegisters().setFlag(FLAG_N);

  //Store the new value in memory.
  getMemory().putByte(getRegisters().getReg16(HL), newValue);
}

/*
 * dec_r16(int) / DEC r16
 * Decrement the value in r16 by one. Does NOT affect flags.
 */
void gb::dec_r16(int reg16){
  uint16_t newValue = getRegisters().getReg16(reg16) - 1;
  getRegisters().setReg16(reg16, newValue);
}

/*
 * inc(int) / INC r8
 * Increment the value in r8.
 */
void gb::inc(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t newValue = source + 1;
  
  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we overflow from bit 3, set the H flag.
  if((source & 0x0f) + 1 > 0x0f) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //Since we are doing an add, set N to zero.
  getRegisters().clearFlag(FLAG_N);

  //Set the register value.
  getRegisters().setReg8(reg8, newValue);
}

/*
 * inc_hl() / INC [HL]
 * Increment the value of the byte pointed to by HL.
 */
void gb::inc_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t newValue = source + 1;
  
  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we overflow from bit 3, set the H flag.
  if((source & 0x0f) + 1 > 0x0f) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //Since we are doing an add, set N to zero.
  getRegisters().clearFlag(FLAG_N);

  //Set the byte value in memory.
  getMemory().putByte(getRegisters().getReg16(HL), newValue);
}

/*
 * inc_r16() / INC r16
 * Increment the value in r16. Does NOT affect flags.
 */
void gb::inc_r16(int r16){     //INC r16
    getRegisters().setReg16(r16, (getRegisters().getReg16(r16) + 1) );
}

/*
 * sbc(int) / SBC A,r8
 * Subtract the value in r8 plus the carry flag from A.
 */
void gb::sbc(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - (source + getRegisters().getFlag(FLAG_C));

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow from bit 4, set the h flag.
  if( ((source + getRegisters().getFlag(FLAG_C)) & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the carry flag (i.e. if r8 + carry > A), set the carry flag.
  if( (source + getRegisters().getFlag(FLAG_C)) > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set flag n.
  getRegisters().setFlag(FLAG_N);

  //Set the register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * sbc_n(uint8_t) / SBC A,n8
 * Subtract the value n8 plus the carry flag from A.
 */
void gb::sbc_n(uint8_t value){
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - (value + getRegisters().getFlag(FLAG_C));

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow from bit 4, set the h flag.
  if( ((value + getRegisters().getFlag(FLAG_C)) & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the carry flag (i.e. if n8 + carry > A), set the carry flag.
  if( (value + getRegisters().getFlag(FLAG_C)) > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set flag n.
  getRegisters().setFlag(FLAG_N);

  //Set the register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * sbc_hl() / SBC A,[HL]
 * Subtract the value of the byte pointed to by HL plus the carry flag from A.
 */
void gb::sbc_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - (source + getRegisters().getFlag(FLAG_C));

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow from bit 4, set the h flag.
  if( ((source + getRegisters().getFlag(FLAG_C)) & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the carry flag (i.e. if [HL] + carry > A), set the carry flag.
  if( (source + getRegisters().getFlag(FLAG_C)) > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set flag n.
  getRegisters().setFlag(FLAG_N);

  //Set the register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * sub(int) / SUB A,r8
 * Subtract the value in r8 from A.
 */
void gb::sub(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - source;

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow from bit 4, set the h flag.
  if((source & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the carry flag (i.e. if r8 > A), set the carry flag.
  if(source > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set flag n.
  getRegisters().setFlag(FLAG_N);

  //Set the register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * sub_n(uint8_t) / SUB A,n8
 * Subtract the value n8 from A.
 */
void gb::sub_n(uint8_t value){
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - value;

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow from bit 4, set the h flag.
  if((value & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the carry flag (i.e. if r8 > A), set the carry flag.
  if(value > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set flag n.
  getRegisters().setFlag(FLAG_N);

  //Set the register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * sub_hl() / SUB A,[HL]
 * Subtract the value of the byte pointed to by HL from A.
 */
void gb::sub_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = dest - source;

  //If the new value is zero, set the z flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //If we borrow from bit 4, set the h flag.
  if((source & 0x0f) > (dest & 0x0f)) getRegisters().setFlag(FLAG_H);
  else getRegisters().clearFlag(FLAG_H);

  //If we borrow from the carry flag (i.e. if r8 > A), set the carry flag.
  if(source > dest) getRegisters().setFlag(FLAG_C);
  else getRegisters().clearFlag(FLAG_C);

  //Since we are doing a subtract, always set flag n.
  getRegisters().setFlag(FLAG_N);

  //Set the register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * op_xor(int) / XOR A,r8
 * XOR the value in r8 with A.
 */
void gb::op_xor(int reg8){
  uint8_t source = getRegisters().getReg8(reg8);
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source ^ dest;

  //If the value is zero, set the flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For XOR, always set: Flag N: 0, Flag H: 0, Flag C: 0
  getRegisters().clearFlag(FLAG_N);
  getRegisters().clearFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  //Set register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * op_xor_n / XOR A,n8
 * XOR the value n8 with A.
 */
void gb::op_xor_n(uint8_t value){
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = value ^ dest;

  //If the value is zero, set the flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For XOR, always set: Flag N: 0, Flag H: 0, Flag C: 0
  getRegisters().clearFlag(FLAG_N);
  getRegisters().clearFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  //Set register value.
  getRegisters().setReg8(A, newValue);
}

/*
 * op_xor_hl() / XOR A,[HL]
 * XOR the value of the byte pointed to by HL with A.
 */
void gb::op_xor_hl(){
  uint8_t source = getMemory().getByte(getRegisters().getReg16(HL));
  uint8_t dest = getRegisters().getReg8(A);
  uint8_t newValue = source ^ dest;

  //If the value is zero, set the flag.
  if(newValue) getRegisters().clearFlag(FLAG_Z);
  else getRegisters().setFlag(FLAG_Z);

  //For XOR, always set: Flag N: 0, Flag H: 0, Flag C: 0
  getRegisters().clearFlag(FLAG_N);
  getRegisters().clearFlag(FLAG_H);
  getRegisters().clearFlag(FLAG_C);

  //Set register value.
  getRegisters().setReg8(A, newValue);
}