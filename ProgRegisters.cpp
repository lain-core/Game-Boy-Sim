#include <cstdint>
#include <iomanip>
#include <iostream>
#include "Registers.h"

Registers::Registers(){
	reset();
}

void Registers::setReg(int reg, uint8_t regVal){
	regs[reg] = regVal;
}

void Registers::setBigReg(int reg, uint16_t regVal){
	bigRegs[reg] = regVal;
}

uint8_t Registers::getReg(int reg){
	return regs[reg];
}

uint16_t Registers::getBigReg(int reg){
	return bigRegs[reg];
}

void Registers::reset(){
	for(int i = 0; i < (NUM_REGISTERS + 2); i++){
		regs[i] = 0;
	}
}
