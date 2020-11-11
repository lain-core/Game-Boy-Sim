#include "../gb.h"

/*
 * call(uint16_t) / CALL n16
 * Call address n16. This pushes the address of the instruction after the CALL on the stack, such that RET can pop it later; then, it executes an implicit JP n16.
 */
void gb::call(uint16_t address){
    push(pc+1);
    pc = address;
}

/*
 * call_cc(bool, uint16_t) / CALL cc,n16
 * Call address n16 if condition cc is met.
 */
void gb::call_cc(bool flag, uint16_t address){
    if(flag){
        push(pc+1);
        pc = address;
    }
}

/*
 * jp_hl() / JP HL
 * Jump to address in HL.
 */
void gb::jp_hl(){
    pc = getRegisters().getReg16(HL);
}

/*
 * jp(uint16_t) / JP n16
 * Jump to address n16.
 */
void gb::jp(uint16_t address){
    pc = address;
}

/*
 * jp_cc(int, uint16_t) / JP cc,n16
 * Jump to address n16 if condition cc is met.
 */
void gb::jp_cc(bool flag, uint16_t address){
    if(flag){
        pc = address;
    }

}

/*
 * jr(uint8_t) / JR e8
 * Relative Jump by adding e8 to the address of the instruction following the JR. To clarify, an operand of 0 is equivalent to no jumping.
 */
void gb::jr(uint8_t offset){
    uint16_t newPC = (pc + 1) + offset;
    pc = newPC;
}

/*
 * jr_cc(int, uint8_t) / JR cc,e8
 * Relative Jump by adding e8 to the current address if condition cc is met.
 */
void gb::jr_cc(bool flag, uint8_t offset){
    if(flag){
        uint16_t newPC = (pc + 1) + offset;
        pc = newPC;
    }
}

/*
 * ret() / RET
 * Return from subroutine. This is basically a POP PC.
 */
void gb::ret(){
    //Grab the stack pointer.
    uint16_t stackptr = getRegisters().getReg16(SP);
    //Grab the high byte.
    uint8_t high = getMemory().getByte(stackptr);
    stackptr++;
    //Grab the low byte.
    uint8_t low = getMemory().getByte(stackptr);
    stackptr++;
    uint16_t value = ((high << 8) | low);
    //Put the value into our PC.
    getRegisters().setReg16(pc, value);
    //Set SP to the new stack pointer we've calculated.
    getRegisters().setReg16(SP, stackptr);
}

/*
 * ret_cc(int) / RET cc
 * Return from subroutine if condition cc is met.
 */
void gb::ret_cc(bool flag){
    if(flag){
        //Grab the stack pointer.
        uint16_t stackptr = getRegisters().getReg16(SP);
        //Grab the high byte.
        uint8_t high = getMemory().getByte(stackptr);
        stackptr++;
        //Grab the low byte.
        uint8_t low = getMemory().getByte(stackptr);
        stackptr++;
        uint16_t value = ((high << 8) | low);
        //Put the value into our PC.
        getRegisters().setReg16(pc, value);
        //Set SP to the new stack pointer we've calculated.
        getRegisters().setReg16(SP, stackptr);
    }
}

/*
 * reti() / RETI
 * Return from subroutine and enable interrupts. This is basically equivalent to executing EI then RET.
 */
void gb::reti(){
    ei();
    ret();
}

/*
 * rst(uint8_t) / RST vec
 * Call address vec. This is a shorter and faster equivalent to CALL for suitable values of vec.
 * Important note: 0xFF is the opcode for RST 0x38, but we should NEVER execute opcode 0xFF.
 */
void gb::rst(uint8_t vec){
    for(int i = 0; i < NUM_VECTORS; i++){
        if(vec == vectors[i]){
            push(pc+1);
            pc = vec;
        }
    }
}