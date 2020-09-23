// sim.h
// This file includes typedefs and constants used by all classes

#ifndef SIM_H
#define SIM_H

#define MEMORY_SIZE 0xFFFF //bytes

/* Important Memory Locations */
#define RSI                 0x0000 //RSI is ReStart and Interrupt Vectors.
#define RSI_END             0x00FF
#define CART_HEADER         0x0100
#define CART_HEADER_END     0x014F
#define ROM                 0x0150
#define ROM_END             0x3FFF
#define BANK                0x4000 //0x4000-0x7FFF is reserved for Switchable ROM banks
#define BANK_END            0x7FFF
#define VRAM_START          0x8000
#define VRAM_END            0x97FF
#define BG_DATA_1           0x9800 //BG Map Data is split into two chunks.
#define BG_DATA_1_END       0x9BFF
#define BG_DATA_2           0x9C00
#define BG_DATA_2_END       0x9FFF
#define COLOR3              0x0F380F // closest to black
#define COLOR2              0x306230
#define COLOR1              0x8bac0f
#define COLOR0              0x9bbc0f  // closest to white
#define CART_RAM            0xA000 //Some carts contain their own RAM.
#define CART_RAM_END        0xBFFF
#define RAM_BANK0           0xC000 //Internal ram Bank 0
#define RAM_BANK0_END       0xCFFF
#define RAM_BANKS17         0xD000 //Internal ram Banks 1-7. Switchable on Game Boy Color only.
#define RAM_BANKS17_END     0xDFFF
#define OAM                 0xFE00
#define OAM_END             0xFE9F //Object Attribute Memory
#define HWIO_START          0xFF00 //Hardware I/O Registers.
#define HWIO_END            0xFF7F
#define INTERRUPT_FLAG      0xFFFF

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
//8-Bit Register F's low bits are always set to zero. The upper 4 are used as flags.
#define flagc   (1 << 4) //Carry Flag
#define flagh   (1 << 5) //Half Carry Flag
#define flagn   (1 << 6) //Add/Sub-Flag
#define flagz   (1 << 7) //Zero Flag

/* Major Opcodes */

#endif
