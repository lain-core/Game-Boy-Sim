#include <iostream>
#include "gb.h"

gb::gb(){
	reset();
}

void gb::reset(){
	cycles = 0;
	pc = 0;
}

// using namespace std;
int main(){
	gb myGB;
	myGB.load("Tetris_World_Rev_1.gb");
	myGB.getMemory().dumpROM();
	uint8_t * miniPix;
	miniPix = (myGB.getPixel().getRowColor(0x5030));
    for (int i = 0; i < 8; i++){
        printf("%d ", miniPix[i]);
    }
	printf("\n");
	myGB.trace();
}

/*
 * trace
 * Trace shows the contents of our 8- and 16-bit Program Registers, as well as the last utilized location in memory and it's contents.
 */
void gb::trace(){
	printf("------------------------------------------------\n");
	printf("The contents of the 8- and 16-bit registers are:\n");
	printf("A: 0x%x F: 0x%x\nB: 0x%x C: 0x%x\nD: 0x%x E: 0x%x\nH: 0x%x L: 0x%x\n", getRegisters().getReg8(A), getRegisters().getReg8(F), getRegisters().getReg8(B), getRegisters().getReg8(C) , getRegisters().getReg8(D), getRegisters().getReg8(E), getRegisters().getReg8(H), getRegisters().getReg8(L));
	printf("AF: 0x%x, BC: 0x%x, DE: 0x%x, HL: 0x%x, SP: 0x%x\n", getRegisters().getReg16(AF), getRegisters().getReg16(BC), getRegisters().getReg16(DE), getRegisters().getReg16(HL), getRegisters().getReg16(SP));
	printf("Last used Memory location: 0x%x, which contains:\n", getMemory().trace());
	printf("------------------------------------------------\n");
}