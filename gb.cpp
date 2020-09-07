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
	myGB.getMemory().dumpROM();
	
}

void gb::reset(){
	cycles = 0;
}
