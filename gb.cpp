#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <cstdint>
#include "gb.h"

gb::gb(){
	reset();
}
// using namespace std;
int main(){
	gb myGB;
	myGB.load("Tetris_World_Rev_1.gb");
	//myGB.getMemory().dumpROM();
	printf("Reg A: %d\n", myGB.getRegisters().getReg(A));
	printf("Reg AF: %d\n", myGB.getRegisters().getBigReg(AF));
	myGB.getRegisters().setBigReg(AF, 0x7F);
	printf("Reg A: %d\n", myGB.getRegisters().getReg(A));
	printf("Reg F: %d\n", myGB.getRegisters().getReg(F));
	printf("Reg AF: %d\n", myGB.getRegisters().getBigReg(AF));
}

void gb::reset(){
	cycles = 0;
}
