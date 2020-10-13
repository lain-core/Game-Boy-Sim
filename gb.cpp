#include <iostream>
#include "gb.h"
gb myGB;

gb::gb(){
	reset();
}

void gb::reset(){
	ime = false;
	cycles = 0;
	//FIXME: We are temporarily using 0x100 as our starting PC because we have not yet implemented the GB bootstrap rom.
	pc = 0x0100;
}

void sigint_handler(int signum){
	printf("Force Quitting...\n");
	myGB.trace();
	exit(signum);
}

int main(int argc, char** argv){
	signal(SIGINT, sigint_handler);
	if(argc == 1){
		printf("No rom specified, loading asm/first.gb (if it exists).\n");
		myGB.setStatus(myGB.load("asm/first.gb"));
	}
	else{
		printf("Loading %s", argv[1]);
		myGB.setStatus(myGB.load(argv[1]));
	}
	printf("File loaded successfully: %d\n", myGB.getStatus());
	//myGB.getMemory().dumpROM();
	
	//Primary Event Loop.
	while(myGB.getStatus()){
		myGB.setStatus(myGB.decode(myGB.getMemory().getWord(myGB.pc++)));
	}
	myGB.trace();
}

/*
 * trace
 * Trace shows the contents of our 8- and 16-bit Program Registers, as well as the last utilized location in memory and it's contents.
 */
void gb::trace(){
	printf("-----------------------------------------------------------\n");
	printf("Program Counter is at: 0x%04x, which contains: 0x%02x\n", pc, getMemory().getByte(pc));
	printf("The contents of the 8- and 16-bit registers are:\n");
	printf("A: 0x%02x F: 0x%02x\nB: 0x%02x C: 0x%02x\nD: 0x%02x E: 0x%02x\nH: 0x%02x L: 0x%02x\n", getRegisters().getReg8(A), getRegisters().getReg8(F), getRegisters().getReg8(B), getRegisters().getReg8(C) , getRegisters().getReg8(D), getRegisters().getReg8(E), getRegisters().getReg8(H), getRegisters().getReg8(L));
	printf("AF: 0x%04x, BC: 0x%04x, DE: 0x%04x, HL: 0x%04x, SP: 0x%04x\n", getRegisters().getReg16(AF), getRegisters().getReg16(BC), getRegisters().getReg16(DE), getRegisters().getReg16(HL), getRegisters().getReg16(SP));
	printf("Flag state: H: %d, C: %d, N: %d, Z: %d\n", getRegisters().getFlag(FLAG_H), getRegisters().getFlag(FLAG_C), getRegisters().getFlag(FLAG_N), getRegisters().getFlag(FLAG_Z));
	printf("Memory Error: %d\n", getMemory().isMemError());
	printf("Last used Memory location: 0x%04x, which contains: %02x\n", getMemory().trace(), getMemory().getByte(getMemory().trace()));
	printf("-----------------------------------------------------------\n");
}