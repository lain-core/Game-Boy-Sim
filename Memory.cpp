#include <iostream>
#include <iomanip>
#include "Memory.h"
// btw baddy stands for byte address
Memory::Memory(){
	reset();
}

void Memory::reset(void){
	for(int i = 0; i < MEMORY_SIZE; i++){
		mem[i] = 0;
	}
	lastUsed = 0;
	memError = false;
}

uint16_t Memory::trace(){
	return lastUsed;
}

uint8_t Memory::getByte(uint16_t baddy)
{
	lastUsed = baddy;
	if (baddy >= 0 && baddy < MEMORY_SIZE){
		return mem[baddy];
	}
	else{
		memError = true;
		return 0;
	}
}

uint8_t * Memory::getTile(uint16_t baddy)
{
	lastUsed = baddy;
	if (VRAM_START <= baddy && (baddy + 15) <= VRAM_END){
		return &(mem[baddy]);
	}
	else
	{
		memError = true;
		return 0;
	}
}

void Memory::putByte(uint16_t baddy, uint8_t val)
{
	lastUsed = baddy;
	if (baddy < MEMORY_SIZE){
		mem[baddy] = val;
	}
	else{
		memError = true;
	}

}

void Memory::putTile(uint16_t baddy, uint8_t val[16]){
	lastUsed = baddy;
	if (VRAM_START <= baddy && (baddy + 15) <= VRAM_END){	
		for (int i = 0; i < 16; i++) mem[baddy + i] = val[i];
	}
	else{
		memError = true;
	}
}

void Memory::dumpROM(void){
	// uint8_t prevLine[16];
	uint8_t currLine[16];
	// initializing arrays to 0
	for (int i = 0; i < 16; i++){
		// prevLine[i] = 0;
		currLine[i] = 0;
	}
	for (int i = CART_HEADER; i < ROM_END; i+=16){
		for (int j = 0; j < 16; j++){
			currLine[j] = getByte(i + j);
		}
			// printing out the correct address and formatting
			std::cout << std::endl << std::setw(4) << std::setfill('0') << std::hex << i << ": ";
			// printing out the contents of the address in 16 bytes per line
			for (int j = 0; j < 16; j++){
				std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(currLine[j]) << " ";			
			} 
	}
	std::cout << std::endl;
}

void Memory::dumpVRAM(void){
	// uint8_t prevLine[16];
	uint8_t currLine[16];
	// initializing arrays to 0
	for (int i = 0; i < 16; i++)
	{
		// prevLine[i] = 0;
		currLine[i] = 0;
	}
	for (int i = VRAM_START; i < VRAM_END; i += 16)
	{
		for (int j = 0; j < 16; j++)
		{
			currLine[j] = getByte(i + j);
		}
		// printing out the correct address and formatting
		std::cout << std::endl
				  << std::setw(4) << std::setfill('0') << std::hex << i << ": ";
		// printing out the contents of the address in 16 bytes per line
		for (int j = 0; j < 16; j++)
		{
			std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(currLine[j]) << " ";
		}
	}
	std::cout << std::endl;
}