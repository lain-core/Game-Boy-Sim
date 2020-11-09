#include <iomanip>
#include <iostream>
#include "Registers.h"

Registers::Registers(){
	reset();
}

void Registers::reset(){
	for(int i = 0; i < NUM_16REGISTERS; i++){
		regs.reg16[i] = 0;
	}
}

/*
 * getReg8 
 * Using a pre-defined register macro (Sim.h), fetches the contents of an 8-bit register.
 */
uint8_t Registers::getReg8(int reg){
	return (regs.reg8[reg]);
}

/*
 * getReg16
 * Using a pre-defined register macro (Sim.h), fetches the contents of a 16-bit register.
 */
uint16_t Registers::getReg16(int reg){
	return (regs.reg16[reg]);
}

/*
 * setReg8
 * Using a pre-defined register macro (Sim.h) and a value, sets an 8-bit register value.
 */
void Registers::setReg8(int reg, uint8_t regVal){
	regs.reg8[reg] = regVal;
}

/*
 * setReg16
 * Using a pre-defined register macro (Sim.h) and a value, sets a 16-bit register value.
 */
void Registers::setReg16(int reg, uint16_t regVal){
	regs.reg16[reg] = regVal;
	printf("\nregVal: %02x\n", regVal);
}

/*
 * getFlag
 * Using a pre-defined flag bit macro (Sim.h), gets a flag value.
 */
bool Registers::getFlag(uint8_t flag){
	return ((getReg8(F) & (1 << flag)) >> flag);
}

/*
 * setFlag
 * Using a pre-defined flag bit macro (Sim.h), sets a flag value.
 */
void Registers::setFlag(uint8_t flag){
	setReg8(F, (getReg8(F) | (1 << flag)));
}

/*
 * clearFlag
 * Using a pre-defined flag bit macro (Sim.h), resets a flag value.
 */
void Registers::clearFlag(uint8_t flag){
	setReg8(F, (getReg8(F) & (~(1 << flag))));
}
