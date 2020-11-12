#include "../gb.h"

/*
 * void rl(int) / RL r8
 * Rotate bits in register R8 left thru carry.
 */
void gb::rl(int regnum){
    uint8_t regval = getRegisters().getReg8(regnum);
    //We need to see if the high bit of our value is 1 in order to set the carry at end.
    bool carry = (regval) >> 7;
    printf("our initial value is: %02x.\nour new carry bit will be: %d\n", regval, carry);
    //Shift our value left to get the new value.
    regval = regval << 1;
    //Check if the carry is set. If it is, set our lowest order bit to 1.
    if(getRegisters().getFlag(FLAG_C)){
        regval  = regval | 0x01;
    }
    //If we needed to use our high bit to set carry, do so now.
    if(carry) getRegisters().setFlag(FLAG_C);
    else getRegisters().clearFlag(FLAG_C);

    if(regval) getRegisters().clearFlag(FLAG_Z);
    else getRegisters().setFlag(FLAG_Z);
    //Always set H and N to zero.
    getRegisters().clearFlag(FLAG_H);
    getRegisters().clearFlag(FLAG_N);
    //At the end, set our new rotated value into our register.
    getRegisters().setReg8(regnum, regval);
}
//RL[HL] 
//RLA **
/*
 * void rla() / RLA
 * Rotate register A left thru carry.
 */
void gb::rla(){
    uint8_t regval = getRegisters().getReg8(A);
    //We need to see if the high bit of our value is 1 in order to set the carry at end.
    bool carry = (regval) >> 7;
    //Shift our value left to get the new value.
    regval = regval << 1;
    //Check if the carry is set. If it is, set our lowest order bit to 1.
    if (getRegisters().getFlag(FLAG_C))
    {
        regval = regval | 0x01;
    }
    //If we needed to use our high bit to set carry, do so now.
    if (carry)getRegisters().setFlag(FLAG_C);
    else getRegisters().clearFlag(FLAG_C);

    //Always set Z, H and N to zero.
    getRegisters().clearFlag(FLAG_Z);
    getRegisters().clearFlag(FLAG_H);
    getRegisters().clearFlag(FLAG_N);
    //At the end, set our new rotated value into our register.
    getRegisters().setReg8(A, regval);
}
//RLC r8
//RLC[HL] 
//RLCA
//RR r8
//RR[HL] 
//RRA
//RRC r8
//RRC[HL] 
//RRCA
//SLA r8
//SLA[HL] 
//SRA r8
//SRA[HL] 
//SRL r8
//SRL[HL]