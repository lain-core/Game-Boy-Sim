#include <cstdint>
#include <iomanip>
#include <iostream>
#include "Registers.h"

Registers::Registers(){
	reset();
}

void Registers::setReg(int reg, uint8_t regVal){
	regs.reg8[reg] = regVal;
}

void Registers::setBigReg(int reg, uint16_t regVal){
	regs.reg16[reg] = regVal;
}

uint8_t Registers::getReg(int reg){
	return (regs.reg8[reg]);
}

uint16_t Registers::getBigReg(int reg){
	return (regs.reg16[reg]);
}

void Registers::reset(){
	for(int i = 0; i < NUM_16REGISTERS; i++){
		regs.reg16[i] = 0;
	}
}