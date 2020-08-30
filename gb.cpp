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
}

void gb::reset(){
	cycles = 0;
}
