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
    getRegisters().setFlag(FLAG_C);
}

/*
 * ccf
 * Complements the carry flag.
 */
void gb::ccf(){
    if(getRegisters().getFlag(FLAG_C)){
        getRegisters().clearFlag(FLAG_C);
    }
    else getRegisters().setFlag(FLAG_C);
}