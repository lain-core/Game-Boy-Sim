#include "../gb.h"

/*
 * gb::ld(int, int) // LD R8, R8
 * Copy value in right register into the left.
 */
void gb::ld(int src, int dst){
    getRegisters().setReg8(dst, getRegisters().getReg8(src));
}

/*
 * gb::ld_n(int) // LD r8, n8
 * Load value n8 into register r8.
 */
void gb::ld_n(int reg8, uint8_t value){
    getRegisters().setReg8(reg8, value);
}

/*
 * gb::ld_r16 // LD r16, n16
 * Load value n16 into register r16.
 */
void gb::ld_r16(int reg, uint16_t value){
    getRegisters().setReg16(reg, value);
}