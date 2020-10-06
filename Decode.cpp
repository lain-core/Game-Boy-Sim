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
void gb::decode(uint16_t opcodewithdata){
    bool ligma = false;
    ligma = decode_misc(opcodewithdata);
    ligma = decode_bitops(opcodewithdata);
}

bool gb::decode_misc(uint16_t opcodewithdata){
    uint8_t opcode = (opcodewithdata & 0xFF00) >> 8;
    printf("Original opcode is: %x, Opcode is: %x\n", opcodewithdata, opcode);
    bool found_inst = true;
    switch(opcode){
        case 0x00: //nop
            nop();
            break;
        case 0x76: //halt
            halt();
            break;
        case 0x10: //stop
            stop();
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

bool gb::decode_bitops(uint16_t opcodewithdata){
    return false;
}