// sim.h
// This file includes typedefs and constants used by all classes

#ifndef SIM_H
#define SIM_H

#define MEMORY_SIZE 8192 //8-bit bytes
#define ROM_START 0x0150
#define ROM_END 0x3FFF

#define NUM_REGISTERS 6 //16-bit registers
#define AF 0
#define BC 1
#define DE 2
#define HL 3
#define SP 4

//Flags Register bit number definitions
#define cy 4 //Carry Flag
#define h  5 //Half Carry Flag
#define n  6 //Add/Sub-Flag
#define zf 7 //Zero Flag

/* Major Opcodes */

#endif
