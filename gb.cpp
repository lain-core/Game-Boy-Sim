#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstdint>
#include "gb.h"
#include "Memory.h"

gb::gb(){
	reset();
}
// using namespace std;
int main(){
	gb myGB;
	Memory mem;
	uint8_t smile [] = {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x24 ,0xFF, 0x00, 0xFF, 0x42, 0xFF, 0x7E, 0xFF, 0x00, 0xFF, 0x00}; 
	myGB.getMemory().putTile(VRAM_END - 0xF, smile);
	// printf("%d\n", myGB.getMemory().getByte(VRAM_END - 0xF));
	myGB.getMemory().dumpVRAM();
}

void gb::reset(){
	cycles = 0;
}
