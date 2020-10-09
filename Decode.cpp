#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstdint>
#include "gb.h"
#include "Sim.h"

/*
 * decode
 * Using a byte passed by gb, we parse out into groups of opcodes to do further work.
 */
bool gb::decode(uint16_t opcodewithdata){
    uint8_t opcode = (opcodewithdata & 0xFF00) >> 8;
    uint8_t data = (opcodewithdata & 0x00FF);
    //Update our status if we can find our opcode. If it passes every function without being found, it must be an illegal (or unimplemented) op.
    bool stat = decode_misc(opcode, data);
    if(!stat) stat = decode_math(opcode, data);
    if(!stat) stat = decode_bitops(opcode, data);
    return stat;
}

bool gb::decode_misc(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    switch(opcode){
        case 0x00: //nop
            nop();
            break;
        case 0x76: //halt
            halt();
            found_inst = false;
            break;
        case 0x10: //stop is a 16-bit instruction, 0x1000. If we have data following our stop, it may be a different op!
            if(data == 0x00) stop();
            else found_inst = false;
            break;
        case 0x37: //scf
            scf();
            break;
        case 0x3F: //ccf
            ccf();
            break;
        case 0xF3: //di
            di();
            break;
        case 0xFB: //ei
            ei();
            break;
        case 0x2F: //cpl
            cpl();
            break;
        case 0x27: //daa
            daa();
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}

bool gb::decode_math(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    switch(opcode){
        case 0x09:
            add_r16(BC);
            break;
        case 0x19:
            add_r16(DE);
            break;
        case 0x29:
            add_r16(HL);
            break;
        case 0x39:
            add_r16(SP);
            break;
        case 0xC6: //add_n(uint8_t) / add a,n8
            add_n(data);
            break;
        //add(int) / add a,r8
        case 0x80:
            add(B); 
        case 0x81:
            add(C);
            break;
        case 0x82:
            add(D);
            break;
        case 0x83:
            add(E);
            break;
        case 0x84:
            add(H);
            break;
        case 0x85:
            add(L);
            break;
        case 0x86: //add_sp() / add a,HL
            add_sp();
            break;
        case 0x87:
            add(A);
            break;
        default:
            found_inst = false;
            break;
    }
}

bool gb::decode_bitops(uint8_t opcode, uint8_t data){
    return false;
}