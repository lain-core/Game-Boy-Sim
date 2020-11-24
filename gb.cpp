#include <iostream>
#include <csignal>
#include <chrono>
#include <thread>
#include "gb.h"
gb myGB;

gb::gb(){
	reset();
}

void gb::reset(){
	ime = false;
	cycles = 0;
	getMemory().putByte(0xFF47, 0xE4); //Initialize our color palette.
	//FIXME: We are temporarily using 0x100 as our starting PC because we have not yet implemented the GB bootstrap rom.
	pc = PC_START;
	ppu.addMem(&memory);
}

void sigint_handler(int signum){
	printf("Force Quitting...\n");
	myGB.trace();
	exit(signum);
}

int main(int argc, char** argv){
	signal(SIGINT, sigint_handler);
	if(argc == 1){
		printf("No rom specified, loading asm/DMG_ROM.bin (if it exists).\n");
		myGB.setStatus(myGB.load("asm/DMG_ROM.bin"));
	}
	else{
		printf("Loading %s\n", argv[1]);
		myGB.setStatus(myGB.load(argv[1]));
	}
	printf("File loaded successfully: %d\n", myGB.getStatus());
	//While GB is still running, run every 16ms (60 FPS).
	//FIXME: Check that Memory::getTileRow() is constructed correctly; Memory should be Little endian, so I think this is how this should go in.
	uint8_t smileyTile[16] = {0x00, 0xFF, 0x00,0xFF,
							  0x24, 0xFF, 0x00,0xFF,
							  0x42, 0xFF, 0x7E,0xFF,
							  0x00, 0xFF, 0x00,0xFF};
	for(int i = 0; i < 16; i++){
		uint16_t baddy = 0x8800 + i;
		myGB.getMemory().putByte(baddy, smileyTile[i]);
		printf("memory at %04x is now: %02x\n", baddy, myGB.getMemory().getByte(baddy));
	}
	
	myGB.getMemory().putByte(LCD_CONTROL, 0x81); //Sets the bits 0 and 7 (LCD_ENABLE and BG_DISPLAY)
	myGB.getPPU().render_tiles();
	/* Main loop
	while(myGB.getStatus()){
		int frameCount = 0;
		while(frameCount < FRAMES_PER_SECOND){
			myGB.run();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
			frameCount++;
		}
	}*/
}

void gb::run(){
	//Primary Event Loop.
	while(((myGB.getCycles() % CYCLES_PER_FRAME) != 0 || myGB.getCycles() == 0) && myGB.getStatus()){
		//myGB.getMemory().putByte(0x0100, 0x76);
		if(myGB.getMemory().getByte(pc) == 0x50) printf("last instruction in bootrom!\n");
		myGB.setStatus(myGB.decode(myGB.getMemory().getByte(myGB.pc++)));
		myGB.trace();
		//myGB.getMemory().dump(0x0134, 0x014D);
		//update timers
		//update graphics
		//do interrupts
	}
	//Update graphics.
}

/*
 * trace
 * Trace shows the contents of our 8- and 16-bit Program Registers, as well as the last utilized location in memory and it's contents.
 */
void gb::trace(){
	printf("-----------------------------------------------------------\n");
	printf("Current cycle: %d Status is: %d\n", myGB.getCycles(), myGB.getStatus());
	printf("Program Counter is at: 0x%04x, which contains: 0x%02x\n", pc, getMemory().getByte(pc));
	printf("The contents of the 8- and 16-bit registers are:\n");
	printf("A: 0x%02x F: 0x%02x\nB: 0x%02x C: 0x%02x\nD: 0x%02x E: 0x%02x\nH: 0x%02x L: 0x%02x\n", getRegisters().getReg8(A), getRegisters().getReg8(F), getRegisters().getReg8(B), getRegisters().getReg8(C) , getRegisters().getReg8(D), getRegisters().getReg8(E), getRegisters().getReg8(H), getRegisters().getReg8(L));
	printf("AF: 0x%04x, BC: 0x%04x, DE: 0x%04x, HL: 0x%04x, SP: 0x%04x\n", getRegisters().getReg16(AF), getRegisters().getReg16(BC), getRegisters().getReg16(DE), getRegisters().getReg16(HL), getRegisters().getReg16(SP));
	printf("Flag state: H: %d, C: %d, N: %d, Z: %d\n", getRegisters().getFlag(FLAG_H), getRegisters().getFlag(FLAG_C), getRegisters().getFlag(FLAG_N), getRegisters().getFlag(FLAG_Z));
	printf("Memory Error: %d\n", getMemory().isMemError());
	printf("Last used Memory location: 0x%04x, which contains: %02x\n", getMemory().trace(), getMemory().getByte(getMemory().trace()));
	printf("-----------------------------------------------------------\n");
}