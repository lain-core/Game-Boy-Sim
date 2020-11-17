// sim.h
// This file includes typedefs and constants used by all classes

#ifndef SIM_H
#define SIM_H

#define MEMORY_SIZE 0xFFFF //bytes
#define NUM_VECTORS 8
#define CYCLES_PER_SECOND 4194304 //Ref from pandocs
#define FRAMES_PER_SECOND 60
#define CYCLES_PER_FRAME  (CYCLES_PER_SECOND / FRAMES_PER_SECOND)


/* Important Memory Locations */
//#define PC_START            0x0000
#define PC_START            0x0100  
//FIXME: change this later when we go to run the boot rom
#define RSI                 0x0000 //RSI is ReStart and Interrupt Vectors.
#define RSI_END             0x00FF
#define CART_HEADER         0x0100
#define CART_HEADER_END     0x014F
#define ROM                 0x0150
#define ROM_END             0x3FFF
#define BANK                0x4000 //0x4000-0x7FFF is reserved for Switchable ROM banks
#define BANK_END            0x7FFF
#define VRAM                0x8000
#define VRAM_END            0x97FF
#define BG_DATA_1           0x9800 //BG Map Data is split into two chunks.
#define BG_DATA_1_END       0x9BFF
#define BG_DATA_2           0x9C00
#define BG_DATA_2_END       0x9FFF
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
#define STACK_START         0xFFFE
#define INTERRUPT_FLAG      0xFFFF

/* CPU Macros */
/* 8-bit Program Register Values */
#define NUM_8REGISTERS 8
#define F 0
#define A 1
#define C 2
#define B 3
#define E 4
#define D 5
#define L 6
#define H 7
#define NOT_AN_8BIT 8

/* 16-bit Program Register Values */
#define NUM_16REGISTERS 5
#define AF 0
#define BC 1
#define DE 2
#define HL 3
#define SP 4

/* Flags register bit number definitions */
//8-Bit Register F's low bits are always set to zero. The upper 4 are used as flags.
#define FLAG_C   4 //Carry Flag
#define FLAG_H   5 //Half Carry Flag
#define FLAG_N   6 //Add/Sub-Flag
#define FLAG_Z   7 //Zero Flag

/* PPU related macros */
// LCD Control Register values
#define BG_DISPLAY          0   // draw background if enabled
#define OBJ_DISPLAY         1   // draw sprites if enabled
#define OBJ_SIZE            2   // size of sprites that need to draw 8x8 or 8x16
#define BG_MAP_SELECT       3   // specifies range of tile set for background not window
#define GB_WINDOW_SELECT    4   // specifies tile id number -> if signed and what range
#define WIN_DISPLAY_ENABLE  5   // draw window if enabled
#define WIN_TILE_SELECT     6   // specifies range of tile set for window drawing
#define LCD_DISPLAY         7   // draw lcd if enabled 

/* Memory locations tied to PPU Registers. */
#define LCD_CONTROL 0xFF40 //LCD Control Register
#define LCD_STATUS  0xFF41 //LCD Status Register
#define SCROLL_Y    0xFF42 //The Y position of BACKGROUND to start drawing from.
#define SCROLL_X    0xFF43 //The X position of BACKGROUND to start drawing from.
#define LY          0xFF44 //The LY indicates the vertical line to which data is transferred to the LCD Driver.
#define LYC         0xFF45 //The GB permanently compares LYC and LY. When both values match, the bit in STAT is set.
#define DMA         0xFF46 //Writing to this register launches DMA from ROM/RAM to OAM.
#define BGP         0xFF47 //BG Palette Data.
#define OBP0        0xFF48 //Obj palette 0 data -> assigns gray shades for sprite palette 0.
#define OPB1        0xFF49 //Obj palette 1 data -> assigns gray shades for sprite palette 1.
#define WINDOW_Y    0xFF4A //The Y position of VIEWING AREA to start drawing from.
#define WINDOW_X    0xFF4B //The X position -7 of VIEWING AREA to start drawing from.

/* Sound related Macros */
/* Sound Channel 1 */
#define NR10        0xFF10 //Channel 1 Sweep register
#define NR11        0xFF11 //Channel 1 Sound length/Wave pattern
#define NR12        0xFF12 //Channel 1 Volume Envelope
#define NR13        0xFF13 //Channel 1 Frequency lo
#define NR14        0xFF14 //Channel 1 Frequency hi

/* Sound Channel 2 */
#define NR21        0xFF16 //Channel 2 Sound Length/Wave Pattern
#define NR22        0xFF17 //Channel 2 Volume Envelope
#define NR23        0xFF18 //Channel 2 Frequency Lo Data
#define NR24        0xFF19 //Channel 2 Frequency Hi Data.

/* Sound Channel 3 */
#define NR30        0xFF1A //Channel 3 Sound on/off.
#define NR31        0xFF1B //Channel 3 Sound Lengh
#define NR32        0xFF1C //Channel 3 Select output level
#define NR33        0xFF1D //Channel 3 Frequency's Lower Data
#define NR34        0xFF1E //Channel 3 Frequency's higher data.

/* Sound Channel 4 - Noise */
#define NR41        0xFF20 //Channel 4 Sound Length
#define NR42        0xFF21 //Channel 4 Volume Envelope
#define NR43        0xFF22 //Channel 4 Polynomial Calculator
#define NR44        0xFF23 //Channel 4 Counter/consecutive

/* Sound Control Registers */
#define NR50        0xFF24 //Channel control / ON-OFF
#define NR51        0xFF25 //Selection of sound output terminal.
#define NR52        0xFF26 //Sound on/off

/* Joypad Input */
#define P1          0xFF00

/* Timer and Divider Registers */
#define DIV         0xFF04 //Divider Register
#define TIMA        0xFF05 //Timer Counter
#define TMA         0xFF06 //Timer Modulo
#define TAC         0xFF07 //Timer Control

/* Interrupts */
#define IE          0xFFFF //Interrupt Enable
#define IF          0xFF0F //Interrupt Flag

/* Miscellaneous Macros*/
/* Color Macros */
#define COLOR0              0x9bbc0f  // closest to white
#define COLOR1              0x8bac0f
#define COLOR2              0x306230
#define COLOR3              0x0F380F // closest to black

#endif
