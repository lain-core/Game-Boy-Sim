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
void gb::decode(uint16_t opcode){
    decode_misc(opcode);
}

bool gb::decode_misc(uint16_t opcode){
    bool found_inst = true;
    switch(opcode){
        case 0x0000: //nop
            nop();
            break;
        case 0x0076: //halt
            halt();
            break;
        case 0x1000: //stop
            stop();
            break;
        case 0x0037: //scf
            scf();
            break;
        case 0x003F: //ccf
            ccf();
            break;
        case 0x00F3: //di
            di();
            break;
        case 0x00FB: //ei
            ei();
            break;
        case 0x002F: //cpl
            cpl();
            break;
        case 0x0027: //daa
            daa();
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}