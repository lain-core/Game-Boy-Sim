#include "../gb.h"
#include "../Sim.h"

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
void gb::ld_r16(int reg16, uint16_t value){
    getRegisters().setReg16(reg16, value);
}

/*
 * gb::ld_hlr // LD [HL], r8
 * Load value in r8 into byte pointed to by register HL.
 */
void gb::ld_hlr(int r8){
    uint8_t value = getRegisters().getReg8(r8);
    getMemory().putByte(getRegisters().getReg16(HL), value);
}

/*
 * gb::ld_hln // LD [HL], n8
 * Load value n8 into byte pointed to by register HL.
 */
void gb::ld_hln(uint8_t value){
    getMemory().putByte(getRegisters().getReg16(HL), value);
}

/*
 * gb::ld_rhl // LD r8, [HL]
 * Load value into register r8 from byte pointed to by register HL.
 */
void gb::ld_rhl(int r8){
    uint8_t value = getMemory().getByte(getRegisters().getReg16(HL));
    getRegisters().setReg8(r8, value);
}

/*
 * gb::ld_r16A // LD [r16], A
 * Store value in register A into byte pointed to by register r16.
 */
void gb::ld_r16A(int r16){
    uint8_t value = getMemory().getByte(getRegisters().getReg8(A));
    getMemory().putByte(getRegisters().getReg16(r16), value);
}

/*
 * gb::ld_n16A // LD [n16], A
 * Store value in register A into byte n16.
 */
void gb::ld_n16A(uint16_t immediate){
    std::cout << "LD [n16], A" << std::endl;
    uint8_t value = getMemory().getByte(getRegisters().getReg8(A));
    getMemory().putByte(getMemory().getByte(immediate), value);
}

/*
 * gb::ldh_n16A // LDH [n16], A
 * Store value in register A into byte n16, if it is within $FF00 and $FFFF
 */
void gb::ldh_n16A(uint16_t immediate){
    uint16_t value = getMemory().getByte(immediate);
    if ((0xFF00 < value) && (value > 0xFFFF)){
        getMemory().putByte(getMemory().getByte(immediate), value);
    }
}

/*
 * gb::ldh_c(int) // LDH [C],A
 * Store value in register A into byte at address $FF00+C.
 */
void gb::ldh_c(uint8_t offset){
    uint16_t final_addr = 0xFF00 + offset;
    getMemory().putByte(final_addr, getRegisters().getReg8(A));
}

/*
 * gb::ld_r16(int) // LD A,[r16]
 * Load value in register A from byte pointed to by register r16
 */
void gb::ld_r16(int reg16){
    uint8_t value = getMemory().getByte(getRegisters().getReg16(reg16));
    getRegisters().setReg8(A, value);
}

/*
 * gb::ld_n16(uint16_t) // LD A,[n16]
 * Load value in register A from byte at address n16.
 */
void gb::ld_n16(uint16_t address){
    uint16_t value = getMemory().getByte(address);
    getRegisters().setReg8(A, value);
}

/*
 * gb::ldh_n16(uint16_t) // LDH A,[n16]
 * Load value in register A from byte at address n16, provided it is b/w 0xFF00 and 0xFFFF.
 */
void gb::ldh_n16(uint16_t address){
    uint8_t value = getMemory().getByte(address);
    getRegisters().setReg8(A, value);
}

/*
 * gb::ldh_c(int) // LDH A,[C]
 * Load value in register A from byte at address 0xFF00+c.
 */
void gb::ldh_c_a(uint8_t offset){
    uint16_t address = 0xFF00 + offset;
    uint8_t value = getMemory().getByte(address);
    getRegisters().setReg8(A, value);
}

/*
 * gb::ld_hli(void) // LD [HLI],A
 * Store value in register A into byte pointed to by HL and then increment HL.
 */
void gb::ld_hli(){
    uint16_t address = getRegisters().getReg16(HL);
    uint8_t value = getRegisters().getReg8(A);
    getMemory().putByte(address, value);
    address++;
    getRegisters().setReg16(HL, address);
}

/*
 * gb::ld_hld(void) // LD [HLD],A
 * Store value in register A into byte pointed to by HL and then decrement HL.
 */
void gb::ld_hld(){
    uint16_t address = getRegisters().getReg16(HL);
    uint8_t value = getRegisters().getReg8(A);
    getMemory().putByte(address, value);
    address--;
    getRegisters().setReg16(HL, address);
}

/*
 * gb::ld_hld_a(void) // LD A,[HLD]
 * Load value into register A from byte pointed to by HL and decrement HL after.
 */
void gb::ld_hld_a(){
    uint16_t address = getRegisters().getReg16(HL);
    uint8_t value = getMemory().getByte(address);
    getRegisters().setReg8(A, value);
    address--;
    getRegisters().setReg16(HL, address);
}

/*
 * gb::ld_hli_a(void) // LD A,[HLI]
 * Load value into Register A from byte pointed to by HL and increment HL after.
 */
void gb::ld_hli_a(){
    uint16_t address = getRegisters().getReg16(HL);
    uint8_t value = getMemory().getByte(address);
    getRegisters().setReg8(A, value);
    address++;
    getRegisters().setReg16(HL, address);
}