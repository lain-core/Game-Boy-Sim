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
void gb::decode(uint8_t opcode){
    decode_misc(opcode);
}

bool gb::decode_misc(uint8_t opcode){
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