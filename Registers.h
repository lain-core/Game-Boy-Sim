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

	//Public functions
	public:		
		Registers();
		void reset(void);
		uint8_t getReg8(int);
		uint16_t getReg16(int);
		void setReg8(int, uint8_t);
		void setReg16(int, uint16_t);
		void setFlags(bool, bool, bool, bool);
};

#endif