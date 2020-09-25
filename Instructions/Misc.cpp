#include "../gb.h"

/*
 * nop
 * No-OPeration. Spends 1 cycle doing nothing.
 */
void gb::nop(){
    return;
}

/*
 * halt
 * Stops the operation of the GB-CPU.
 */
void gb::halt(){
    status = false;
}

/*
 * stop
 * Stops the operation of the GB-CPU.
 */
void gb::stop(){
    status = false;
}

/*
 * scf
 * Sets the carry flag.
 */
void gb::scf(){
    getRegisters().clearFlag(FLAG_N);
    getRegisters().clearFlag(FLAG_H);
    getRegisters().setFlag(FLAG_C);
}

/*
 * ccf
 * Complements the carry flag.
 */
void gb::ccf(){
    getRegisters().clearFlag(FLAG_N);
    getRegisters().clearFlag(FLAG_H);
    if(getRegisters().getFlag(FLAG_C)){
        getRegisters().clearFlag(FLAG_C);
    }
    else getRegisters().setFlag(FLAG_C);
}

/*
 * di
 * Disables interrupts by clearing the Interrupt Master Enable flag.
 */
void gb::di(){
    ime = false;
}

/*
 * ei
 * Enables interrupts by setting the Interrupt Master Enable flag.
 */
void gb::ei(){
    ime = true;
}

/*
 * cpl
 * ComPLements the Accumulator.
 */
void gb::cpl(){
    getRegisters().setReg8(A, (~getRegisters().getReg8(A)));
}