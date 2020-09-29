#include <iostream>
#include "gb.h"

gb::gb(){
	reset();
}

void gb::reset(){
	ime = false;
	cycles = 0;
	pc = 0;
}

// using namespace std;
int main(){
	gb myGB;
	//myGB.load("Tetris_World_Rev_1.gb");
	//myGB.getMemory().dumpROM();
	uint8_t * miniPix;
	miniPix = (myGB.getPixel().getRowColor(0x5030));
    for (int i = 0; i < 8; i++){
        printf("%d ", miniPix[i]);
    }
	printf("\n");
	//myGB.trace();
	myGB.scf();
	std::cout << "cflag: " << myGB.getRegisters().getFlag(FLAG_C) << std::endl;
	myGB.ccf();
	std::cout << "cflag: " << myGB.getRegisters().getFlag(FLAG_C) << std::endl;
	myGB.ccf();
	std::cout << "cflag: " << myGB.getRegisters().getFlag(FLAG_C) << std::endl;
}

/*
 * trace
 * Trace shows the contents of our 8- and 16-bit Program Registers, as well as the last utilized location in memory and it's contents.
 */
void gb::trace(){
	printf("------------------------------------------------\n");
	printf("The contents of the 8- and 16-bit registers are:\n");
	printf("A: 0x%02x F: 0x%02x\nB: 0x%02x C: 0x%02x\nD: 0x%02x E: 0x%02x\nH: 0x%02x L: 0x%02x\n", getRegisters().getReg8(A), getRegisters().getReg8(F), getRegisters().getReg8(B), getRegisters().getReg8(C) , getRegisters().getReg8(D), getRegisters().getReg8(E), getRegisters().getReg8(H), getRegisters().getReg8(L));
	printf("AF: 0x%04x, BC: 0x%04x, DE: 0x%04x, HL: 0x%04x, SP: 0x%04x\n", getRegisters().getReg16(AF), getRegisters().getReg16(BC), getRegisters().getReg16(DE), getRegisters().getReg16(HL), getRegisters().getReg16(SP));
	printf("Last used Memory location: 0x%04x, which contains:\n", getMemory().trace());
	printf("------------------------------------------------\n");
}