#include <cstdint>
#include <iomanip>
#include <iostream>
#include "Registers.h"

Registers::Registers(){
	reset();
}

void Registers::setReg8(int reg, uint8_t regVal){
	regs.reg8[reg] = regVal;
}

void Registers::setReg16(int reg, uint16_t regVal){
	regs.reg16[reg] = regVal;
}

uint8_t Registers::getReg8(int reg){
	return (regs.reg8[reg]);
}

uint16_t Registers::getReg16(int reg){
	return (regs.reg16[reg]);
}

void Registers::setFlags(bool z, bool n, bool h, bool c){
	setReg8(F, 0);
	uint8_t finalFlag = 0;
	if(z) finalFlag = finalFlag | flagz;
	if(n) finalFlag = finalFlag | flagn;
	if(h) finalFlag = finalFlag | flagh;
	if(c) finalFlag = finalFlag | flagc;
	setReg8(F, finalFlag);
}

void Registers::reset(){
	for(int i = 0; i < NUM_16REGISTERS; i++){
		regs.reg16[i] = 0;
	}
}