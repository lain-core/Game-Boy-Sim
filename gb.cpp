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
	myGB.load("Tetris.gb");
	myGB.getMemory().dump();
	unsigned char value = myGB.getMemory().getByte(ROM_START);
	std::cout << "Byte at 0x0150: " << std::hex << value << std::endl;
}

void gb::reset(){
	cycles = 0;
}
