// sim.h
// This file includes typedefs and constants used by all classes

#ifndef SIM_H
#define SIM_H

#define MEMORY_SIZE 8192 //8-bit bytes

/* Important Memory Locations */
#define ROM_START 0x0150
#define ROM_END 0x3FFF

/* 8-bit Program Register Values */
#define NUM_8REGISTERS 8
#define A 0
#define F 1
#define B 2
#define C 3
#define D 4
#define E 5
#define H 6
#define L 7

/* 16-bit Program Register Values */
#define NUM_16REGISTERS 5
#define AF 0
#define BC 1
#define DE 2
#define HL 3
#define SP 4

/* Flags register bit number definitions */
#define cy 4 //Carry Flag
#define h  5 //Half Carry Flag
#define n  6 //Add/Sub-Flag
#define zf 7 //Zero Flag

/* Major Opcodes */

#endif
