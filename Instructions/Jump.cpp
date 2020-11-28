#include "../gb.h"

uint16_t ideal_return_address;
/*
 * call(uint16_t) / CALL n16
 * Call address n16. This pushes the address of the instruction after the CALL on the stack, such that RET can pop it later; then, it executes an implicit JP n16.
 */
void gb::call(uint16_t offset){
    ideal_return_address = pc;
    printf("calling, ret to pc value 0x%04x\n", ideal_return_address);
    push_val(pc);
    pc = PC_START + offset;
}

/*
 * call_cc(bool, uint16_t) / CALL cc,n16
 * Call address n16 if condition cc is met.
 */
void gb::call_cc(bool flag, uint16_t offset){
    if(flag){
        push_val(pc);
        pc = PC_START + offset;
        cycles += 3;
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
void gb::jr(int8_t offset){
    printf("pc in jr is: %04x\n", pc);
    printf("offset: %02x\n", offset);
    printf("final pc is: 0x%04x\n", (pc+offset));
    pc += offset;
}

/*
 * jr_cc(int, uint8_t) / JR cc,e8
 * Relative Jump by adding e8 to the current address if condition cc is met.
 */
void gb::jr_cc(bool flag, int8_t offset){
    if(flag){
        printf("pc in jr_cc is: %04x\n", pc);
        printf("offset: %02x\n", offset);
        printf("Final pc is: 0x%04x\n", (pc+offset));
        pc += offset;
    }
}

/*
 * ret() / RET
 * Return from subroutine. This is basically a POP PC.
 */
void gb::ret(){
    printf("pc entering RET is: %04x\n", pc);
    uint16_t newpc = pop_val();
    pc = newpc;
    printf("new pc after RET is: %04x\n", pc);
    printf("new pc SHOULD be 0x%04x\n", ideal_return_address);
}

/*
 * ret_cc(int) / RET cc
 * Return from subroutine if condition cc is met.
 */
void gb::ret_cc(bool flag){
    if(flag){
        uint16_t newpc = pop_val();
        printf("pc entering RETI is: 0x%04x\n", pc);
        pc = newpc;
        printf("new pc after RETI is: %04x\n", pc);
        printf("new pc SHOULD be 0x%04x\n", ideal_return_address);
        //Set SP to the new stack pointer we've calculated.
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