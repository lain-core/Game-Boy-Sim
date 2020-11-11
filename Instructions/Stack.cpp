#include "../gb.h"

/*
 * add_hl_sp() / ADD HL,SP
 * Add the value in SP to HL.
 */
void gb::add_hl_sp(){
    uint16_t source = getRegisters().getReg16(SP);
    uint16_t dest = getRegisters().getReg16(HL);
    uint16_t newValue = source + dest;
    //Always clear the Z flag.
    getRegisters().clearFlag(FLAG_Z);

	//If we carry the bit from the lower byte, set the h flag.
	if((source & 0x00ff) + (dest & 0x00ff) > 0x00ff) getRegisters().setFlag(FLAG_H);
	else getRegisters().clearFlag(FLAG_H);

	//If we carry the bit from the full add, set the c flag.
	if(source + dest > 0xffff) getRegisters().setFlag(FLAG_C);
	else getRegisters().clearFlag(FLAG_C);

	//Always clear flag N because we are doing an add.
	getRegisters().clearFlag(FLAG_N);
    
    getRegisters().setReg16(HL, newValue);
}

/*
 * add_sp_e8() // ADD SP,e8
 * Add the signed value e8 to SP.
 */
void gb::add_sp_e8(int8_t value){
    //TODO: confused
}

/*
 * dec_sp() / DEC SP
 * Decrement the value in register SP by 1.
 */
void gb::dec_sp(){
    uint16_t stackptr = getRegisters().getReg16(SP);
    stackptr--;
    getRegisters().setReg16(SP, stackptr);
}

/*
 * inc_sp() / INC SP
 * Increment the value in register SP by 1.
 */
void gb::inc_sp(){
    uint16_t stackptr = getRegisters().getReg16(SP);
    stackptr++;
    getRegisters().setReg16(SP, stackptr);
}

/*
 * ld_sp() / LD SP,n16
 * Load value n16 into SP.
 */
void gb::ld_sp(uint16_t address){
    getRegisters().setReg16(SP, address);
}

/*
 * ld_n_sp() / LD [n16], SP
 * Load value in SP to the byte pointed to by n16.
 */
void gb::ld_n_sp(uint16_t address){
    uint16_t stackptr = getRegisters().getReg16(SP);
    uint8_t high = ((stackptr & 0xFF00) >> 8);
    uint8_t low = (stackptr & 0x00FF);
    printf("high byte is: %02x\nlow byte is: %02x\n", high, low);
    getMemory().putByte(address, low);
    address++;
    getMemory().putByte(address, high);
    getRegisters().setReg16(SP, stackptr);
}

/*
 * ld_hl_e8 / LD HL,SP+e8
 * Add the signed value e8 to SP and store the result in HL.
 */
void gb::ld_hl_e8(int8_t value){
    //TODO: me confuse
}

/*
 * ld_sp_hl() / LD SP, HL
 * Load register HL into register SP.
 */
void gb::ld_sp_hl(void){
    uint16_t value = getRegisters().getReg16(HL);
    getRegisters().setReg16(SP, value);
}

/*
 * pop(int) / POP r16
 * Pop register r16 from the stack.
 * For the sake of simplicity, we re-use this for POP AF.
 */
void gb::pop(int reg16){
    //Grab the stack pointer.
    uint16_t stackptr = getRegisters().getReg16(SP);
    //Grab the high byte.
    uint8_t high = getMemory().getByte(stackptr);
    stackptr++;
    //Grab the low byte.
    uint8_t low = getMemory().getByte(stackptr);
    stackptr++;
    uint16_t value = ((high << 8) | low);
    //Put the value into our register of choice.
    getRegisters().setReg16(reg16, value);
    //Set SP to the new stack pointer we've calculated.
    getRegisters().setReg16(SP, stackptr);
}

/*
 * push(int) / PUSH r16
 * Push the value of r16 onto the stack.
 * For sake of simplicity, we re-use this for PUSH AF.
 */
void gb::push(int reg16){
    printf("In push for register %d\n", reg16);
    //Grab the stack pointer.
    uint16_t stackptr = getRegisters().getReg16(SP);
    //Grab the value out of our register and split it into hi and lo.
    uint16_t reg_value = getRegisters().getReg16(reg16);
    uint16_t high_val = reg_value & 0xF0;
    uint16_t low_val = reg_value;
    stackptr--;
    getMemory().putByte(stackptr, high_val);
    stackptr--;
    getMemory().putByte(stackptr, low_val);
    //Set SP to the new stack pointer we've calculated.
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
