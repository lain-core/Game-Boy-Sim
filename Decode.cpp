#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstdint>
#include "gb.h"
#include "Sim.h"
#include "Tools.h"

/*
 * gb::decode(uint16_t)
 * Using a byte passed by gb, we parse out into groups of opcodes to do further work.
 */
bool gb::decode(uint8_t opcode){
    //Update our status if we can find our opcode. If it passes every function without being found, it must be an illegal (or unimplemented) op.
    bool found = decode_misc(opcode);
    if(!found){ found = decode_math(opcode); }
    if(!found){ found = decode_bitops(opcode); }
    if(!found){ found = decode_load(opcode); }
    if(!found){ found = decode_stackops(opcode); }
    if(!found){ found = decode_jump(opcode); }
    if(found && getStatus()) return true; //If we found our instruction, but our instruction led to the state of the GB cpu being set to false, then quit.
    else return false;
}

bool gb::decode_load(uint8_t opcode){
	bool found_inst = true;
    int regnum = get_regnum(opcode);
	//All LD r8s fall within range 0x40 - 0x7F
	if((opcode & 0xF0) >= 0x40 && (opcode & 0xF0) <= 0x47){
		if(opcode == 0x46) ld_hl_r8(B);
		else ld(regnum, B);
	}
	else if((opcode & 0xF0) >= 0x48 && (opcode & 0xF0) <= 0x4F){
		if(opcode == 0x4E) ld_hl_r8(C);
		else ld(regnum, C);
	}
	else if((opcode & 0xF0) >= 0x50 && (opcode & 0xF0) <= 0x57){
		if(opcode == 0x56) ld_hl_r8(D);
		else ld(regnum, D);
	}
	else if((opcode & 0xF0) >= 0x58 && (opcode & 0xF0) < 0x5F){
		if(opcode == 0x5E) ld_hl_r8(E);
		else ld(regnum, E);
	}
	else if((opcode & 0xF0) >= 0x60 && (opcode & 0xF0) <= 0x67){
		if(opcode == 0x66) ld_hl_r8(H);
		else ld(regnum, H);
	}
	else if((opcode & 0xF0) >= 0x68 && (opcode & 0xF0) <= 0x6F){
		if(opcode == 0x6E) ld_hl_r8(L);
		else ld(regnum, L);
	}
	else if((opcode & 0xF0) >= 0x70 && (opcode & 0xF0) <= 0x77){
		if(opcode == 0x76) found_inst = false;
		else ld_hl(regnum);
	}
	else if((opcode & 0xF0) >= 0x78 && (opcode & 0xF0) <= 0x7F){
		if(opcode == 0x7E) ld_hl_r8(A);
		else ld(regnum, A);
	}
    else{
		switch(opcode){
        	case 0x01:
                ld_r16(BC, getWordData());
                break;
        	case 0x11:
                ld_r16(DE, getWordData());
                break;
        	case 0x21:
                ld_r16(HL, getWordData());
                break;
			case 0x02:
				ld_r16A(BC);
				break;
			case 0x12:
				ld_r16A(DE);
				break;
			case 0x22:
				ld_hli();
				break;
			case 0x32:
				ld_hld();
				break;
			case 0x06:
				ld_n(B, getData());
				
				break;
        	case 0x16:
            	ld_n(D, getData());
            	
            	break;
        	case 0x26:
            	ld_n(H, getData());
            	
            	break;
        	case 0x36:
            	ld_hln(getData());
            	
            	break;
        	case 0x0A:
            	ld_a_r16(BC);
            	break;
        	case 0x1A:
            	ld_a_r16(DE);
            	break;
        	case 0x2A:
            	ld_hli_a();
            	break;
        	case 0x3A:
            	ld_hld_a();
            	break;
        	case 0x0E:
            	ld_n(C, getData());
            	
            	break;
        	case 0x1E:
            	ld_n(E, getData());
            	
            	break;
        	case 0x2E:
            	ld_n(L, getData());
            	
            	break;
        	case 0x3E:
            	ld_n(A, getData());
            	
            	break;
        	case 0xE0:
            	ldh_n16A(getData());
            	
            	break;
        	case 0xF0:
            	ldh_n16(getData());
                
                break;
        	case 0xE2:
            	//FIXME: listed as 1 byte???
            	ldh_c();
            	break;
        	case 0xF2:
            	//FIXME: "
            	ldh_c_a();
            	break;
        	case 0xEA:
                ld_n16A(getWordData());
            	break;
        	case 0xFA:
            	ld_n16(getWordData());
            	break;
			default:
				found_inst = false;
				break;
		}
	}
	return found_inst;
}

/*
 * gb::decode_misc(uint8_t, uint8_t)
 * Decode miscellaneous instructions (nop, halt, etc.)
 */
bool gb::decode_misc(uint8_t opcode){
    bool found_inst = true;
    switch(opcode){
        case 0x00: //nop
            nop();
            cycles++;
            break;
        case 0x76: //halt
            halt();
            break;
        case 0x10: //stop is a 16-bit instruction, 0x1000. If we have data following our stop, it may be a different op!
            if(getData() == 0x00){
                stop();
            }
            else found_inst = false;
            break;
        case 0x37: //scf
            scf();
            cycles++;
            break;
        case 0x3F: //ccf
            ccf();
            cycles++;
            break;
        case 0xF3: //di
            di();
            cycles++;
            break;
        case 0xFB: //ei
            ei();
            cycles++;
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
bool gb::decode_math(uint8_t opcode){
    bool found_inst = true;
    //All 8-Bit relevant ops.
    //TODO: fucked up 8-bit info; clean up.
    switch(opcode){
        case 0x3C:
            inc(A);
            cycles++;
            break;
        case 0x04:
            inc(B);
            cycles++;
            break;
        case 0x0C:
            inc(C);
            cycles++;
            break;
        case 0x14:
            inc(D);
            cycles++;
            break;
        case 0x1C:
            inc(E);
            cycles++;
            break;
        case 0x24:
            inc(H);
            cycles++;
            break;
        case 0x2C:
            inc(L);
            cycles++;
            break;
        case 0x3D:
            dec(A);
            cycles++;
            break;
        case 0x05:
            dec(B);
            cycles++;
            break;
        case 0x0D:
            dec(C);
            cycles++;
            break;
        case 0x15:
            dec(D);
            cycles++;
            break;
        case 0x1D:
            dec(E);
            cycles++;
            break;
        case 0x25:
            dec(H);
            cycles++;
            break;
        case 0x2D:
            dec(L);
            cycles++;
            break;
        case 0x34:
            inc_hl();
            cycles += 3;
            break;
        case 0x35:
            dec_hl();
            cycles += 3;
            break;
        case 0xC6:
            add_n(getData());
            cycles += 2;
            break;
        case 0xD6:
            sub_n(getData());
            cycles += 2;
            break;
        case 0xE6:
            op_and_n(getData());
            cycles += 2; 
            break;
        case 0xF6:
            op_or_n(getData());
            cycles += 2;
            break;
        case 0xEE:
            op_xor_n(getData());
            cycles += 2;
            break;
        case 0xCE:
            adc_n(getData());
            cycles ++;
            break;
        case 0xDE:
            sbc_n(getData());
            cycles += 2;
            break;
        case 0xFE:
            cp_n(getData());
            cycles += 2;
            break;
        default:
            found_inst = false;
            break;
    }

    //All instructions operating on 16-bit registers.
    if(!found_inst){
        switch(opcode){
        case 0x03:
            inc_r16(BC);
            cycles += 2;
            break;
        case 0x13:
            inc_r16(DE);
            cycles += 2;
            break;
        case 0x23:
            inc_r16(HL);
            cycles += 2;
            break;
        case 0x09:
            add_r16(BC);
            cycles += 2;
            break;
        case 0x19:
            add_r16(DE);
            cycles += 2;
            break;
        case 0x29:
            add_r16(HL);
            cycles += 2;
            break;
        case 0x39:
            add_r16(SP);
            cycles += 2;
            break;
        case 0x0B:
            dec_r16(BC);
            cycles += 2;
            break;
        case 0x1B:
            dec_r16(DE);
            cycles += 2;
            break;
        case 0x2B:
            dec_r16(HL);
            cycles += 2;
            break;
        default:
            found_inst = false;
            break;
        }
    }

    // uint8_t data = getData();
    //ADD/ADC spans region 0x80 to 0x8F.
    //SUB/SDC spans region 0x90 to 0x9F.
    //AND/XOR spans region 0xA0 to 0xAF.
    //OR/CP spans region 0xB0 eto 0xBF.
    if((opcode & 0xF0) == 0x80) found_inst = decode_add(opcode);
    if((opcode & 0xF0) == 0x90) found_inst = decode_sub(opcode);
    if((opcode & 0xF0) == 0xA0) found_inst = decode_and_xor(opcode);
    if((opcode & 0xF0) == 0xB0) found_inst = decode_or_cp(opcode);
    return found_inst;
}

/*
 *  gb::decode_bitops(uint8_t, uint8_t)
 * 
 */
bool gb::decode_bitops(uint8_t opcode){
    bool found_inst = true;
    //All bitop instructions are prefixed with CB.
    if(opcode == 0xCB){
        printf("found CB! :)\n");
        uint8_t data = getData();
        
        printf("data: %02x\n", data);
        //SWAP spans region 0x30 to 0x37.
        //BIT spans region 0x40 to 0x7F.
        //RES spans region 0x80 to 0xBF.
        //SET spans region 0xC0 to 0xFF.
        if(data >= 0x30 && data <= 0x37){
            int regnum = get_regnum(data);
            if(regnum < NOT_AN_8BIT) swap(regnum);
            else if(regnum == NOT_AN_8BIT) swap_hl();
            else found_inst = false;
        }
        //else if((data & 0xf0) >= 0x00 && (data & 0xf0) <= 0x1F) found_inst = decode_rlc_rrc(data);
        else if((data & 0xf0) >= 0x10 && (data & 0xf0) <= 0x1F) found_inst = decode_rl_rr(data);
        else if((data & 0xf0) >= 0x40 && (data & 0xf0) <= 0x70) found_inst = decode_bit(data);
        else if((data & 0xf0) >= 0x80 && (data & 0xf0) <= 0xB0) found_inst = decode_res(data);
        else if((data & 0xf0) >= 0xC0 && (data & 0xf0) <= 0xF0) found_inst = decode_set(data);
        else found_inst = false;
    }
    else switch(opcode){
        case 0x17:
            rla();
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}

bool gb::decode_stackops(uint8_t opcode){
    bool found_inst = true;
    switch(opcode){
        case 0x39:
            add_hl_sp();
            cycles += 2;
            break;
        case 0x33:
            inc_sp();
            cycles += 2;
            break;
        case 0x3B:
            dec_sp();
            cycles += 2;
            break;
        case 0x31:
            ld_sp(getWordData());
            cycles += 3;
            break;
        case 0x08:
            ld_n_sp(getWordData());
            cycles += 5;
            break;
        case 0xF9:
            ld_sp_hl();
            cycles += 2;
            break;
        case 0xC1:
            pop(BC);
            cycles += 3;
            break;
        case 0xD1:
            pop(DE);
            cycles += 3;
            break;
        case 0xE1:
            pop(HL);
            cycles += 3;
            break;
        case 0xF1:
            pop(AF);
            cycles += 3;
            break;
        case 0xC5:
            push(BC);
            cycles += 3;
            break;
        case 0xD5:
            push(DE);
            cycles += 3;
            break;
        case 0xE5:
            push(HL);
            cycles += 3;
            break;
        case 0xF5:
            push(AF);
            cycles += 4;
            break;
        case 0xF8: //LD HL,SP+8
            found_inst = false;
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}

bool gb::decode_jump(uint8_t opcode){
    bool found_inst = true;
    bool cc = false;
    switch(opcode){
        case 0xCD:
            call(getWordData());
            cycles += 6;
            break;
        case 0xDC:
            cc = getRegisters().getFlag(FLAG_C);
            call_cc(cc, getWordData());
            cycles += 3;
            break;
        case 0xCC:
            cc = getRegisters().getFlag(FLAG_Z);
            call_cc(cc, getWordData());
            cycles += 3;
            break;
        case 0xC4:
            cc = !(getRegisters().getFlag(FLAG_Z));
            call_cc(cc, getWordData());
            cycles += 3;
            break;
        case 0xD4:
            cc = !(getRegisters().getFlag(FLAG_C));
            call_cc(cc, getWordData());
            cycles += 3;
            break;
        case 0x18: //JR r8
            jr(getData());
            cycles += 3;
            break;
        case 0x28: //JR Z,r8
            cc = getRegisters().getFlag(FLAG_Z);
            jr_cc(cc, getData());
            cycles++;
            break;
        case 0x38: //JR C,r8
            cc = getRegisters().getFlag(FLAG_C);
            jr_cc(cc, getData());
            cycles++;
            break;
        case 0x20: //JR NZ,r8
            cc = !(getRegisters().getFlag(FLAG_Z));
            jr_cc(cc, getData());
            cycles++;
            break;
        case 0x30: //JR NC,r8
            cc = !(getRegisters().getFlag(FLAG_C));
            jr_cc(cc, getData());
            cycles++;
            break;
        case 0xC9:
            ret();
            cycles += 4;
            break;
        case 0xD9:
            reti();
            cycles += 4;
            break;
        default:
            found_inst = false;
            break;
    }
    return found_inst;
}

/* Helper Functions */

bool gb::decode_add(uint8_t opcode){
    bool found_inst = true;
    //Cases 0x80 - 0x87 are of the form ADD r8,A.
    //Cases 0x88 - 0x8F are of the form ADC r8,A.
    //Case 0x86 and 0x8E are using [HL] rather than an r8.
    int reg_num = get_regnum(opcode);
    if(opcode >= 0x80 && opcode <= 0x87){
        if(reg_num != NOT_AN_8BIT) add(reg_num);
        else add_hl();
    }
    else if(opcode >= 0x88 && opcode <= 0x8F){
        if(reg_num != NOT_AN_8BIT) adc(reg_num);
        else adc_hl();
    }
    else found_inst = false;
    return found_inst;
}

bool gb::decode_sub(uint8_t opcode){
    bool found_inst = true;
    //Cases 0x90 - 0x97 are of the form SUB r8,A.
    //Cases 0x98 - 0x9F are of the form SBC r8,A.
    //Case 0x96 and 0x9E are using [HL] rather than an r8.
    int reg_num = get_regnum(opcode);
    if(opcode >= 0x90 && opcode <= 0x97){
        if(reg_num != NOT_AN_8BIT) sub(reg_num);
        else sub_hl();
    }
    else if (opcode >= 0x98 && opcode <= 0x9F)
    {
        if(reg_num != NOT_AN_8BIT) sub(reg_num);
        else sub_hl();
    }
    else found_inst = false;
    return found_inst;
}

bool gb::decode_and_xor(uint8_t opcode){
    bool found_inst = true;
    //Cases 0xA0 - 0xA7 are of the form AND r8,A.
    //Cases 0xA8 - 0xAF are of the form XOR r8,A.
    //Case 0xA6 and 0xAE are using [HL] rather than an r8.
    int reg_num = get_regnum(opcode);
    if (opcode >= 0xA0 && opcode <= 0xA7)
    {
        if(reg_num != NOT_AN_8BIT) op_and(reg_num);
        else op_and_hl();
    }
    else if (opcode >= 0xA8 && opcode <= 0xAF)
    {
        if(reg_num < NOT_AN_8BIT) op_xor(reg_num);
        else op_xor_hl();
    }
    else found_inst = false;
    return found_inst;
}

bool gb::decode_or_cp(uint8_t opcode){
    bool found_inst = true;
    //Cases 0xB0 - 0xB7 are of the form OR r8,A.
    //Cases 0xB8 - 0xBF are of the form CP r8,A.
    //Case 0xB6 and 0xBE are using [HL] rather than an r8.
    int reg_num = get_regnum(opcode);
    // printf("called or. reg num is: %x\n", reg_num);
    if (opcode >= 0xB0 && opcode <= 0xB7)
    {
        if(reg_num != NOT_AN_8BIT) op_or(reg_num);
        else op_or_hl();
    }
    else if (opcode >= 0xB8 && opcode <= 0xBF)
    {
        if(reg_num != NOT_AN_8BIT) cp(reg_num);
        else cp_hl();
    }
    else found_inst = false;
    return found_inst;
}

/*
 * decode_rl_rr(uint8_t)
 * Decodes opcodes dedicated to Left and Right rotates.
 */
bool gb::decode_rl_rr(uint8_t opcode){
    bool found_inst = true;
    int regnum = get_regnum(opcode);
    //RL occupies 0x10 - 0x17.
    //0x16 calls RL [HL] rather than RL r8.
    if(opcode <= 0x17){
        if(regnum < NOT_AN_8BIT) rl(regnum);
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
    // printf("calling bit(%d, %d)\n", bit_num, reg_num);
    if(reg_num < NOT_AN_8BIT) bit(bit_num, reg_num);
    else if(reg_num == NOT_AN_8BIT) bit_hl(bit_num);
	else inst_found = false;
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
    // printf("Bit num is: %d, Reg num is: %d\n", bit_num, reg_num);
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
    // printf("data: %x, bitnum: %x, regnum: %x\n", data, bit_num, reg_num);
    return bit_num;
}

uint8_t gb::getData(){
    uint8_t val = getMemory().getByte(pc);
    pc++;
    return val;
}

uint16_t gb::getWordData(){
	uint16_t val = Tools::changeEndian(getMemory().getWord(pc));
    pc+=2;
    return val;
}