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
		uint16_t lastUsed;

	//Public Functions
	public:
		Memory();
		uint8_t		getByte(uint16_t byteAddress);
		void 		putByte(uint16_t byteAddress, uint8_t val);
		uint16_t	getWord(uint16_t byteAddress);
		void 		putTile(uint16_t baddy, uint8_t arr[16]);
		uint8_t *	getTile(uint16_t baddy);
		void 		reset(void);
		void 		dumpROM(void);
		void 		dumpVRAM(void);
		void 		dump(int, int);
		uint16_t	trace(void);
		bool		isMemError(void);
};
#endif
