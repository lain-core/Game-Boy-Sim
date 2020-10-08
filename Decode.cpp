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
    uint8_t opcode = (opcodewithdata & 0xFF00) >> 8;
    uint8_t data = (opcodewithdata & 0x00FF);
    bool ligma = false;
    ligma = decode_misc(opcode, data);
    ligma = decode_bitops(opcode, data);
}

bool gb::decode_misc(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    switch(opcode){
        case 0x00: //nop
            nop();
            break;
        case 0x76: //halt
            halt();
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

bool gb::decode_bitops(uint8_t opcode, uint8_t data){
    return false;
}