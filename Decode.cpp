#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstdint>
#include "gb.h"
#include "Sim.h"
bool was8bit = false;

/*
 * gb::decode(uint16_t)
 * Using a byte passed by gb, we parse out into groups of opcodes to do further work.
 */
bool gb::decode(uint16_t opcodewithdata){
    uint8_t opcode = (opcodewithdata & 0xFF00) >> 8;
    uint8_t data = (opcodewithdata & 0x00FF);
    //Update our status if we can find our opcode. If it passes every function without being found, it must be an illegal (or unimplemented) op.
    bool found = decode_misc(opcode, data);
    if(!found) found = decode_math(opcode, data);
    if(!found) found = decode_bitops(opcode, data);
    if(!found) found = decode_load(opcode, data);
    if(!was8bit) pc++;
    if(found && getStatus()) return found; //If we found our instruction, but our instruction led to the state of the GB cpu being set to false, then quit.
    else return !found;
}

bool gb::decode_load(uint8_t opcode, uint8_t data){
    uint16_t bigdata = getMemory().getWord(pc + 1);
    bool found_inst = true;
    if(opcode == 0xEA){
        printf("got a load smile");
        printf("opcode: %02x data: %02x bigdata: %04x\n", opcode, data, bigdata);
        ld_n16A(data);
    }
    else found_inst = false;
    return found_inst;
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
            was8bit = true;
            break;
        case 0x76: //halt
            halt();
            was8bit = true;
            break;
        case 0x10: //stop is a 16-bit instruction, 0x1000. If we have data following our stop, it may be a different op!
            if(data == 0x00) stop();
            else found_inst = false;
            break;
        case 0x37: //scf
            scf();
            was8bit = true;
            break;
        case 0x3F: //ccf
            ccf();
            was8bit = true;
            break;
        case 0xF3: //di
            di();
            was8bit = true;
            break;
        case 0xFB: //ei
            ei();
            was8bit = true;
            break;
        case 0x2F: //cpl
            cpl();
            was8bit = true;
            break;
        case 0x27: //daa
            daa();
            was8bit = true;
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
    //All 8-Bit relevant ops.
    //TODO: fucked up 8-bit info; clean up.
    switch(opcode){
        case 0x04:
            inc(B);
            was8bit = true;
            break;
        case 0x14:
            inc(D);
            was8bit = true;
            break;
        case 0x24:
            inc(H);
            was8bit = true;
            break;
        case 0x34:
            inc_hl();
            was8bit = true;
            break;
        case 0x05:
            dec(B);
            was8bit = true;
            break;
        case 0x15:
            dec(D);
            was8bit = true;
            break;
        case 0x25:
            dec(H);
            was8bit = true;
            break;
        case 0x35:
            dec_hl();
            was8bit = true;
            break;
        case 0x0C:
            inc(C);
            was8bit = true;
            break;
        case 0x1C:
            inc(E);
            was8bit = true;
            break;
        case 0x2C:
            inc(L);
            was8bit = true;
            break;
        case 0x3C:
            inc(A);
            was8bit = true;
            break;
        case 0x0D:
            dec(C);
            was8bit = true;
            break;
        case 0x1D:
            dec(E);
            was8bit = true;
            break;
        case 0x2D:
            dec(L);
            was8bit = true;
            break;
        case 0x3D:
            dec(A);
            was8bit = true;
            break;
        case 0xC6:
            add_n(data);
            break;
        case 0xD6:
            sub_n(data);
            was8bit = true;
            break;
        case 0xE6:
            op_and_n(data);
            was8bit = true;
            break;
        case 0xF6:
            op_or_n(data);
            was8bit = true;
            break;
        case 0xCE:
            adc_n(data);
            was8bit = true;
            break;
        case 0xDE:
            sbc_n(data);
            was8bit = true;
            break;
        case 0xEE:
            op_xor_n(data);
            was8bit = true;
            break;
        case 0xFE:
            cp_n(data);
            was8bit = true;
            break;
        default:
            found_inst = false;
            break;
    }

    //All 16-bit instructons.
    if(!found_inst){
        switch(opcode){
        case 0x03:
            inc_r16(BC);
            break;
        case 0x13:
            inc_r16(DE);
            break;
        case 0x23:
            inc_r16(HL);
            break;
        case 0x33:
            inc_r16(SP);
            break;
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
        case 0x0B:
            dec_r16(BC);
            break;
        case 0x1B:
            dec_r16(DE);
            break;
        case 0x2B:
            dec_r16(HL);
            break;
        case 0x3B:
            dec_r16(SP);
            break;
        default:
            found_inst = false;
            break;
        }
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
    bool found_inst = true;
    if(opcode == 0xCB){
        printf("found opcode 0xCB!\n");
        if((data & 0xf0) >= 0x40 && (data & 0xf0) <= 0x70){
            printf("calling bit(%02x)\n", data);
            decode_bit(data);
        }
        if((data & 0xf0) >= 0x80 && (data & 0xf0) <= 0xB0){
            decode_res(data);
        }
        if((data & 0xf0) >= 0xC0 && (data & 0xf0) <= 0xF0){
            decode_set(data);
        }
        switch(data){
            case 0x30:
                swap(B);
                break;
            case 0x31:
                swap(C);
                break;
            case 0x32:
                swap(D);
                break;
            case 0x33:
                swap(E);
                break;
            case 0x34:
                swap(H);
                break;
            case 0x35:
                swap(L);
                break;
            case 0x36:
                swap_hl();
                break;
            case 0x37:
                swap(A);
                break;
            default:
                found_inst = false;
                break;
        }
    }
    else found_inst = false;
    return found_inst;
}

/* Helper Functions */

bool gb::decode_add(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    //Cases 0x80 - 0x87 are of the form ADD r8,A.
    //Cases 0x88 - 0x8F are of the form ADC r8,A.
    //Case 0x86 and 0x8E are using [HL] rather than an r8.
    int reg_num = get_regnum(data);
    if(data >= 0x80 && data <= 0x87){
        if(reg_num != NOT_AN_8BIT) add(reg_num);
        else add_hl();
    }
    else if(data >= 0x88 && data <= 0x8F){
        if(reg_num != NOT_AN_8BIT) adc(reg_num);
        else adc_hl();
    }
    else found_inst = false;
    return found_inst;
}

bool gb::decode_sub(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    //Cases 0x90 - 0x97 are of the form SUB r8,A.
    //Cases 0x98 - 0x9F are of the form SBC r8,A.
    //Case 0x96 and 0x9E are using [HL] rather than an r8.
    int reg_num = get_regnum(data);
    if(data >= 0x90 && data <= 0x97){
        if(reg_num != NOT_AN_8BIT) sub(reg_num);
        else sub_hl();
    }
    else if(data >= 0x98 && data <= 0x9F){
        if(reg_num != NOT_AN_8BIT) sub(reg_num);
        else sub_hl();
    }
    else found_inst = false;
    return found_inst;
}

bool gb::decode_and_xor(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    //Cases 0xA0 - 0xA7 are of the form AND r8,A.
    //Cases 0xA8 - 0xAF are of the form XOR r8,A.
    //Case 0xA6 and 0xAE are using [HL] rather than an r8.
    int reg_num = get_regnum(data);
    if(data >= 0xA0 && data <= 0xA7){
        if(reg_num != NOT_AN_8BIT) op_and(reg_num);
        else op_and_hl();
    }
    else if(data >= 0xA8 && data <= 0xAF){
        if(reg_num != NOT_AN_8BIT) op_xor(reg_num);
        else op_xor_hl();
    }
    else found_inst = false;
    return found_inst;
}

bool gb::decode_or_cp(uint8_t opcode, uint8_t data){
    bool found_inst = true;
    //Cases 0xB0 - 0xB7 are of the form OR r8,A.
    //Cases 0xB8 - 0xBF are of the form CP r8,A.
    //Case 0xB6 and 0xBE are using [HL] rather than an r8.
    int reg_num = get_regnum(data);
    printf("called or. reg num is: %x\n", reg_num);
    if(data >= 0xB0 && data <= 0xB7){
        if(reg_num != NOT_AN_8BIT) op_or(reg_num);
        else op_or_hl();
    }
    else if(data >= 0xB8 && data <= 0xBF){
        if(reg_num != NOT_AN_8BIT) cp(reg_num);
        else cp_hl();
    }
    else found_inst = false;
    return found_inst;
}

/*
 * decode_bit(uint8_t)
 * Determines the bit numbers and register numbers and calls out to BIT with the appropriate parameters.
 */
bool gb::decode_bit(uint8_t data){
    bool inst_found = true;
    int bit_num = get_bitnum(data);
    int reg_num = get_regnum(data);
    printf("calling bit(%d, %d)\n", bit_num, reg_num);
    if(reg_num != NOT_AN_8BIT) bit(bit_num, reg_num);
    else bit_hl(bit_num);
    return inst_found;
}

/*
 * decode_res(uint8_t)
 * Determines the bit number and register number and calls to RES with the appropriate parameters.
 */
bool gb::decode_res(uint8_t data){
    bool inst_found = true;
    int bit_num = get_bitnum(data);
    int reg_num = get_regnum(data);
    if(reg_num != NOT_AN_8BIT) res(bit_num, reg_num);
    else res_hl(bit_num);
    return inst_found;
}

/*
 * decode_set(uint8_t)
 * Grabs the bit number and register number to do a SET on, and calls the function with the correct parameters.
 */
bool gb::decode_set(uint8_t data){
    bool inst_found = true;
    int bit_num = get_bitnum(data);
    int reg_num = get_regnum(data);
    printf("Bit num is: %d, Reg num is: %d\n", bit_num, reg_num);
    if(reg_num != NOT_AN_8BIT) set(bit_num, reg_num);
    else set_hl(bit_num);
    return inst_found;
} 

int gb::get_regnum(uint8_t data){
    uint8_t reg_num = (data & 0x0f);
    switch(reg_num % 8){
        case 0:
            reg_num = B;
            break;
        case 1:
            reg_num = C;
            break;
        case 2:
            reg_num = D;
            break;
        case 3:
            reg_num = E;
            break;
        case 4:
            reg_num = H;
            break;
        case 5:
            reg_num = L;
            break;
        case 7:
            reg_num = A;
            break;
        default:
            reg_num = NOT_AN_8BIT;
            break;
    }
    return reg_num;
}

int gb::get_bitnum(uint8_t data){
    uint8_t bit_num = (data & 0xf0) >> 4;
    uint8_t reg_num = (data & 0x0f);
    switch(bit_num % 4){
        case 0:
            if(reg_num <= 7) bit_num = 0;
            if(reg_num >= 8) bit_num = 1;
            break;
        case 1:
            if(reg_num <= 7) bit_num = 2;
            if(reg_num >= 8) bit_num = 3;
            break;
        case 2:
            if(reg_num <= 7) bit_num = 4;
            if(reg_num >= 8) bit_num = 5;
            break;
        case 3:
            if(reg_num <= 7) bit_num = 6;
            if(reg_num >= 8) bit_num = 7;
            break;            
    }
    printf("data: %x, bitnum: %x, regnum: %x\n", data, bit_num, reg_num);
    return bit_num;
}