#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstdint>
#include "gb.h"
#include "Sim.h"

/*
 * gb::decode(uint16_t)
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

/*
 * gb::decode_misc(uint8_t, uint8_t)
 * Decode miscellaneous instructions (nop, halt, etc.)
 */
bool gb::decode_misc(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    switch(opcode){
        case 0x00: //nop
            nop();
            break;
        case 0x76: //halt
            halt();
            return false;
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

/* 
 * gb::decode_math(uint8_t, uint8_t)
 * Decode all Math ops (ADD, SUB, AND, OR, XOR, etc.)
 */
bool gb::decode_math(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    switch(opcode){
        case 0x04:
            inc(B);
            break;
        case 0x14:
            inc(D);
            break;
        case 0x24:
            inc(H);
            break;
        case 0x34:
            inc_hl();
            break;
        case 0x05:
            dec(B);
            break;
        case 0x15:
            dec(D);
            break;
        case 0x25:
            dec(H);
            break;
        case 0x35:
            dec_hl();
            break;
        case 0x0C:
            inc(C);
            break;
        case 0x1C:
            inc(E);
            break;
        case 0x2C:
            inc(L);
            break;
        case 0x3C:
            inc(A);
            break;
        case 0x0D:
            dec(C);
            break;
        case 0x1D:
            dec(E);
            break;
        case 0x2D:
            dec(L);
            break;
        case 0x3D:
            dec(A);
            break;
        case 0xC6:
            add_n(data);
            break;
        case 0xD6:
            sub_n(data);
            break;
        case 0xE6:
            op_and_n(data);
            break;
        case 0xF6:
            op_or_n(data);
            break;
        case 0xCE:
            adc_n(data);
            break;
        case 0xDE:
            sbc_n(data);
            break;
        case 0xEE:
            op_xor_n(data);
            break;
        case 0xFE:
            cp_n(data);
            break;
        default:
            found_inst = false;
            break;
    }
    if((opcode & 0xf0) == 0x80) found_inst = decode_add(opcode, data);
    if((opcode & 0xf0) == 0x90) found_inst = decode_sub(opcode, data);
    if((opcode & 0xf0) == 0xA0) found_inst = decode_and_xor(opcode, data);
    if((opcode & 0xf0) == 0xB0) found_inst = decode_or_cp(opcode, data);
    return found_inst;
}

/*
 *  gb::decode_bitops(uint8_t, uint8_t)
 * 
 */
bool gb::decode_bitops(uint8_t opcode, uint8_t data){
    return false;
}

/* Helper Functions */

bool gb::decode_add(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    switch(opcode){
        //Cases 0x80 - 0x87 are of the form ADD r8,A.
        //Cases 0x88 - 0x8F are of the form ADC r8,A.
        //Case 0x86 and 0x8E are using [HL] rather than an r8.
        case 0x80:
            add(B); 
            break;
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
        case 0x86:
            add_hl();
            break;
        case 0x87:
            add(A);
            break;
        case 0x88:
            adc(B);
            break;
        case 0x89:
            adc(C);
            break;
        case 0x8A:
            adc(D);
            break;
        case 0x8B:
            adc(E);
            break;
        case 0x8C:
            adc(H);
            break;
        case 0x8D:
            adc(L);
            break;
        case 0x8E:
            adc_hl();
            break;
        case 0x8F:
            adc(A);
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}

bool gb::decode_sub(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    //Cases 0x90 - 0x97 are of the form SUB r8,A.
    //Cases 0x98 - 0x9F are of the form SBC r8,A.
    //Case 0x96 and 0x9E are using [HL] rather than an r8.
    switch(opcode){
        case 0x90:
            sub(B);
            break;
        case 0x91:
            sub(C);
            break;
        case 0x92:
            sub(D);
            break;
        case 0x93:
            sub(E);
            break;
        case 0x94:
            sub(H);
            break;
        case 0x95:
            sub(L);
            break;
        case 0x96:
            sub_hl();
            break;
        case 0x97:
            sub(A);
            break;
        case 0x98:
            sbc(B);
            break;
        case 0x99:
            sbc(C);
            break;
        case 0x9A:
            sbc(D);
            break;
        case 0x9B:
            sbc(E);
            break;
        case 0x9C:
            sbc(H);
            break;
        case 0x9D:
            sbc(L);
            break;
        case 0x9E:
            sbc_hl();
            break;
        case 0x9F:
            sbc(A);
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}

bool gb::decode_and_xor(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    //Cases 0xA0 - 0xA7 are of the form AND r8,A.
    //Cases 0xA8 - 0xAF are of the form XOR r8,A.
    //Case 0xA6 and 0xAE are using [HL] rather than an r8.
    switch(opcode){
        case 0xA0:
            op_and(B);
            break;
        case 0xA1:
            op_and(C);
            break;
        case 0xA2:
            op_and(D);
            break;
        case 0xA3:
            op_and(E);
            break;
        case 0xA4:
            op_and(H);
            break;
        case 0xA5:
            op_and(L);
            break;
        case 0xA6:
            op_and_hl();
            break;
        case 0xA7:
            op_and(A);
            break;
        case 0xA8:
            op_xor(B);
            break;
        case 0xA9:
            op_xor(C);
            break;
        case 0xAA:
            op_xor(D);
            break;
        case 0xAB:
            op_xor(E);
            break;
        case 0xAC:
            op_xor(H);
            break;
        case 0xAD:
            op_xor(L);
            break;
        case 0xAE:
            op_xor_hl();
            break;
        case 0xAF:
            op_xor(A);
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}

bool gb::decode_or_cp(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    //Cases 0xB0 - 0xB7 are of the form OR r8,A.
    //Cases 0xB8 - 0xBF are of the form CP r8,A.
    //Case 0xB6 and 0xBE are using [HL] rather than an r8.
    switch(opcode){
        case 0xB0:
            op_or(B);
            break;
        case 0xB1:
            op_or(C);
            break;
        case 0xB2:
            op_or(D);
            break;
        case 0xB3:
            op_or(E);
            break;
        case 0xB4:
            op_or(H);
            break;
        case 0xB5:
            op_or(L);
            break;
        case 0xB6:
            op_or_hl();
            break;
        case 0xB7:
            op_or(A);
            break;
        case 0xB8:
            cp(B);
            break;
        case 0xB9:
            cp(C);
            break;
        case 0xBA:
            cp(D);
            break;
        case 0xBB:
            cp(E);
            break;
        case 0xBC:
            cp(H);
            break;
        case 0xBD:
            cp(L);
            break;
        case 0xBE:
            cp_hl();
            break;
        case 0xBF:
            cp(A);
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}