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
void gb::call_cc(int flagnum, uint16_t address){
    bool flag = getRegisters().getFlag(flagnum);
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
void gb::jp_cc(int flagnum, uint16_t address){
    bool flag = getRegisters().getFlag(flagnum);
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
void gb::jr_cc(int flagnum, uint8_t offset){
    bool flag = getRegisters().getFlag(flagnum);
    if(flag){
        uint16_t newPC = (pc + 1) + offset;
        pc = newPC;
    }
}

//RET       *** BIG DEAL
void gb::ret(){
}

//RET cc
void gb::ret_cc(int flagnum){

}
//RETI
void gb::reti(){

}
//RST vec
void gb::vec(uint8_t vec){

}