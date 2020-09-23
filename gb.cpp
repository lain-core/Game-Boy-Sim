#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstdint>
#include "gb.h"
#include "Memory.h"
#include "Pixel.h"

gb::gb(){
	reset();
}
// using namespace std;
int main(){
	gb myGB;
	Memory mem;
	Pixel pix;

	uint8_t * miniPix;
	miniPix = (pix.getTileColor(0x5030));
}

void gb::reset(){
	cycles = 0;
}

void gb::trace(){
	printf("The contents of the 8 and 16-bit registers are:\n");
	printf("A: %x F: %x\nB: %x C: %x\nD: %x E: %x\nH: %x L: %x\n", getRegisters().getReg8(A), getRegisters().getReg8(F), getRegisters().getReg8(B), getRegisters().getReg8(C) , getRegisters().getReg8(D), getRegisters().getReg8(E), getRegisters().getReg8(H), getRegisters().getReg8(L));
	printf("AF: %x, BC: %x, DE: %x, HL: %x, SP: %x\n", getRegisters().getReg16(AF), getRegisters().getReg16(BC), getRegisters().getReg16(DE), getRegisters().getReg16(HL), getRegisters().getReg16(SP));
	printf("Last used Memory location: 0x%x\n", getMemory().trace());
}