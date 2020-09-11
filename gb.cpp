#include <iostream>
#include <iomanip>
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
	myGB.getRegisters().setReg16(AF, 0x0304);
	std::cout << "Reg A: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(myGB.getRegisters().getReg8(A)) << std::endl;
	std::cout << "Reg F: 0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(myGB.getRegisters().getReg8(F)) << std::endl;
	std::cout << "Reg AF: 0x" << std::setw(4) << std::setfill('0') << std::hex << myGB.getRegisters().getReg16(AF) << std::endl;
}

void gb::reset(){
	cycles = 0;
}
