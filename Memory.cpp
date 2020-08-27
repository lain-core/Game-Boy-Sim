#include <iostream>
#include <iomanip>
#include <cstdint>
#include <array>

#include "Memory.h"
// #include "Tools.h"

Memory::Memory(){
	reset();
}

void Memory::store(uint16_t waddr, uint8_t val){
	if(waddr >= MEMORY_SIZE){
		memError = true;
	}
	else{
		mem[waddr] = val;
	}
}

uint8_t Memory::fetch(uint16_t waddr){
	if(waddr >= MEMORY_SIZE){
		memError = true;
	}
	else{
		return mem[waddr];
	}
	return 0;
}

uint8_t Memory::getByte(uint16_t byteAddress){
	//TODO: Get Byte from memory.
	return 0;
}

void Memory::putByte(uint16_t byteAddress, uint8_t val){
	//TODO: Put a byte in memory.
}

uint8_t Memory::getWord(uint16_t byteAddress){
	//TODO: get a word from memory.
	return 0;
}

void Memory::putWord(uint16_t byteAddress, uint8_t wordValue){
	//TODO: put word in memory.
}

void Memory::reset(void){
	for(int i = 0; i < MEMORY_SIZE; i++){
		mem[i] = 0;
	}
	memError = false;
}
