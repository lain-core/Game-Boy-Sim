#include "../gb.h"

/*
 * bit(int, int) / BIT u3,r8
 * Test bit u3 in register r8, set z flag if bit is 0.
 */
void gb::bit(int bit, int reg8){
    uint8_t mask = 1 << bit;
    uint8_t newValue = (getRegisters().getReg8(reg8) & mask) >> bit;
    printf("in bit(), mask is:%d, newValue is: %d\n", mask, newValue);
    
    //If new value is zero, set Z flag.
    if(newValue) getRegisters().clearFlag(FLAG_Z);
    else getRegisters().setFlag(FLAG_Z);
    //For BIT, always set: Flag N: 0, Flag H: 1, Flag C: Unchanged.
    getRegisters().clearFlag(FLAG_N);
    getRegisters().setFlag(FLAG_H);
}

/*
 * bit_hl(int) / BIT u3,[HL]
 * Test bit u3 against [HL].
 */
void gb::bit_hl(int bit){
    uint8_t mask = 1 << bit;
    uint8_t newValue = (getMemory().getByte(getRegisters().getReg16(HL)) & mask) >> bit;

    //If new value is zero, set Z flag.
    if(newValue) getRegisters().clearFlag(FLAG_Z);
    else getRegisters().setFlag(FLAG_Z);

    //For BIT, always set: Flag N: 0, Flag H: 1, Flag C: Unchanged.
    getRegisters().clearFlag(FLAG_N);
    getRegisters().setFlag(FLAG_H);
}

/*
 * res(int, int) / RES u3,r8
 * Set bit u3 in register r8 to 0.
 */
void gb::res(int bit, int reg8){
    uint8_t src = getRegisters().getReg8(reg8);
    uint8_t mask = 0 << bit;
    
    getRegisters().setReg8(reg8, (src & mask));
}

/*
 * res_hl(int) / RES u3,[HL]
 * Set bit u3 in the byte pointed to by HL to 0.
 */
void gb::res_hl(int bit){
    uint8_t src = getMemory().getByte(getRegisters().getReg16(HL));
    uint8_t mask = ~(1 << bit);

    getMemory().putByte(getRegisters().getReg16(HL), (src & mask));
}

/*
 * set(int, int) / SET u3,r8
 * Set bit u3 in register r8 to 1.
 */
void gb::set(int bit, int reg8){
    uint8_t src = getRegisters().getReg8(reg8);
    uint8_t mask = 1 << bit;

    printf("bit is %d, reg8 is %d, mask is 0x%x, new value is: %x\n", bit, reg8, mask, (src | mask));

    getRegisters().setReg8(reg8, (src | mask));
}

/*
 * set_hl(int) / SET u3,[HL]
 * Set bit u3 in the byte pointed to by register HL to 1.
 */
void gb::set_hl(int bit){
    uint8_t src = getMemory().getByte(getRegisters().getReg16(HL));
    uint8_t mask = 1 << bit;

    getMemory().putByte(getRegisters().getReg16(HL), (src | mask));
}

/*
 * swap / SWAP r8
 * Swap upper 4 bits in register r8 with the lower 4.
 */
void gb::swap(int reg8){
    uint8_t src = getRegisters().getReg8(reg8);
    uint8_t newLow = (src >> 4);
    uint8_t newHigh = (src << 4);
    uint8_t newValue = newLow | newHigh;

    //If new value is zero, set the Z flag.
    if(newValue) getRegisters().clearFlag(FLAG_Z);
    getRegisters().setFlag(FLAG_Z);

    //For SWAP, always set: Flag N: 0, Flag H: 0, Flag C: 0
    getRegisters().clearFlag(FLAG_N);
    getRegisters().clearFlag(FLAG_H);
    getRegisters().clearFlag(FLAG_C);

    //Set new register value.
    getRegisters().setReg8(reg8, newValue);
}

/*
 * swap_hl() / SWAP [HL]
 * Swap upper 4 bits in byte pointed to by [HL] with the lower 4.
 */
void gb::swap_hl(){
    uint8_t src = getMemory().getByte(getRegisters().getReg16(HL));
    uint8_t newLow = (src >> 4);
    uint8_t newHigh = (src << 4);
    uint8_t newValue = newLow | newHigh;

    //If new value is zero, set the Z flag.
    if(newValue) getRegisters().clearFlag(FLAG_Z);
    getRegisters().setFlag(FLAG_Z);

    //For SWAP, always set: Flag N: 0, Flag H: 0, Flag C: 0
    getRegisters().clearFlag(FLAG_N);
    getRegisters().clearFlag(FLAG_H);
    getRegisters().clearFlag(FLAG_C);

    //Set new register value.
    getMemory().putByte(getRegisters().getReg16(HL), newValue);
}