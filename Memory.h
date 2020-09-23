// Memory.h
// Authors: Joe Story, Hunter King

#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint> //fixed-width unsigned ints

#include "Sim.h"

class Memory{

	//Private data
		uint8_t mem[MEMORY_SIZE];
		bool memError;

	//Private functions
		uint8_t fetch	(uint16_t waddr);

	//public stuff
	public:
		Memory();
		void		store(uint16_t waddr, uint8_t val);
		uint64_t 	getLong(int32_t baddy);
		uint8_t		getByte(uint16_t byteAddress);
		void 		putByte(uint16_t byteAddress, uint8_t val);
		void 		putTile(uint16_t baddy, uint8_t arr[16]);
		uint8_t *	getTile(uint16_t baddy);
		void reset(void);
		void 		dumpROM(void);
		void 		dumpVRAM(void);
};
#endif
