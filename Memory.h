// Memory.h
// Authors: Joe Story, Hunter King

#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint> //fixed-width unsigned ints

#include "Sim.h"

class Memory{

	//Private data
		uint8_t mem[MEMORY_SIZE];
		bool memErr;

	//Private functions
		void	store	(uint16_t waddr, uint8_t val);
		uint8_t fetch	(uint16_t waddr);

	//public stuff
	public:
		Memory();
		uint8_t	getByte (uint16_t byteAddress);
		void		putByte (uint16_t byteAddress, uint8_t value);
		uint8_t	getWord (uint16_t byteAddress);
};

#endif
