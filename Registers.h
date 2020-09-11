//Registers.h
//Authors: Joe Story, Hunter King

#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>
#include "Sim.h"



class Registers{

	//Private Data
	typedef union{
		uint8_t reg8[NUM_8REGISTERS + 2];
		uint16_t reg16[NUM_16REGISTERS];
	} regSet;

	regSet regs;

	//Private functions
	public:		
		Registers();
		void setReg(int, uint8_t);
		uint8_t getReg(int);
		uint16_t getBigReg(int);
		void setBigReg(int, uint16_t);
		void reset(void);
};

#endif