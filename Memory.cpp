#include <iostream>
#include <iomanip>
#include <cstdint>
#include <array>
#include "Memory.h"
#include "Tools.h"
// btw baddy stands for byte address
Memory::Memory(){
	reset();
}

void Memory::store(uint16_t baddy, uint8_t val){
	if(baddy >= MEMORY_SIZE){
		memError = true;
	}
	else{
		mem[baddy] = val;
	}
}

uint8_t Memory::fetch(uint16_t baddy){
	if(baddy >= MEMORY_SIZE){
		memError = true;
	}
	else{
		return mem[baddy];
	}
	return 0;
}

uint8_t Memory::getByte(uint16_t baddy)
{
	//TODO: Get Byte from memory.
	if (baddy >= 0 && baddy < MEMORY_SIZE){
		return mem[baddy];
	}
	else{
		memError = true;
		return 0;
	}
}

void Memory::putByte(uint16_t baddy, uint8_t val)
{
	//TODO: Put a byte in memory.
	if (baddy >= 0 && baddy < MEMORY_SIZE){
		mem[baddy] = val;
	}
	else{
		memError = true;
	}
}

void Memory::reset(void){
	for(int i = 0; i < MEMORY_SIZE; i++){
		mem[i] = 0;
	}
	memError = false;
}

uint64_t Memory::getLong(int32_t baddy){
	if (baddy >= 0 && baddy < MEMORY_SIZE && baddy % 8 == 0){
		return Tools::buildWord(mem[baddy], mem[baddy + 1], mem[baddy + 2], mem[baddy + 3], mem[baddy + 4], mem[baddy + 5], mem[baddy + 6], mem[baddy + 7]);
	} 
	return 0;
}

void Memory::dump(void){
	uint64_t prevLine[4] = {0, 0, 0, 0};
	uint64_t currLine[4] = {0, 0, 0, 0};
	int32_t i;
	bool star = false;

	// 32 bytes per line (four 8-byte words)
	for (i = 0; i < MEMORY_SIZE; i += 32)
	{
		// get the values for the current line
		for (int32_t j = 0; j < 4; j++)
			currLine[j] = getLong(i + j * 8);

		// if they are the same as the values in the previous line then
		// don't display them, but always display the first line
		if (i == 0 || currLine[0] != prevLine[0] || currLine[1] != prevLine[1] ||
			currLine[2] != prevLine[2] || currLine[3] != prevLine[3])
		{
			std::cout << std::endl
					  << std::setw(3) << std::setfill('0') << std::hex << i << ": ";
			for (int32_t j = 0; j < 4; j++)
				std::cout << std::setw(8) << std::setfill('0') << std::hex
						  << currLine[j] << " ";
			star = false;
		}
		else
		{
			// if this line is exactly like the previous line then
			// just print a * if one hasn't been printed already
			if (star == false)
				std::cout << "*";
			star = true;
		}
		for (int32_t j = 0; j < 4; j++)
			prevLine[j] = currLine[j];
	}
	std::cout << std::endl;
}
