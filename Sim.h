// sim.h
// This file includes typedefs and constants used by all classes

#ifndef SIM_H
#define SIM_H

#define MEMORY_SIZE 8192 //8-bit bytes

/* Important Memory Locations */
#define ROM_START 0x0150
#define ROM_END 0x3FFF

/* 8-bit Program Register Values */
#define NUM_REGISTERS 8
#define regA 0
#define regF 1
#define regB 2
#define regC 3
#define regD 4
#define regE 5
#define regH 6
#define regL 7

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
