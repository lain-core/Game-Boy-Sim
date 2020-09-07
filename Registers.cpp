#include <cstdint>
#include <iomanip>
#include <iostream>
#include "Registers.h"

Registers::Registers(){
	reset();
}

void Registers::setReg(int reg, uint8_t regVal){
	regs[reg] = &regVal;
}

void Registers::setBigReg(int reg, uint16_t regVal){
	bigRegs[reg] = regVal;
}

uint8_t * Registers::getReg(int reg){
	return regs[reg];
}

uint16_t Registers::getBigReg(int reg){
	return bigRegs[reg];
}

void Registers::reset(){
	for(int i = 0; i < NUM_16REGISTERS; i++){
		bigRegs[i] = 0;
	}	

	for(int i = 0; i < NUM_REGISTERS; i++){
		// if(i % 2 == 0) regs[i] = &bigRegs[i];
		if(i % 2 == 1) regs[i] = regByte(bigRegs, bigRegs[i] >> 8); 
	}
}

uint8_t * Registers::regByte(uint16_t * bigRegs, uint8_t pointer){
	uint8_t * answer;
	int count = 0;
	for (int i = pointer; i < 8; i++){
		answer[count] = bigRegs[i];
		count++;
	}
}

// 16bitarray[AF, BC, DE, HL, stackpointer]
// 8bitarray[&A, &B, &(*BC >> 8), &D, &(*DE >> 8), &H, &(*HL >> 8)];