#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <cstdint>
#include "gb.h"

gb::gb(){
	int thisInt = 0;
}
// using namespace std;
int main(){
	gb myGB;
	myGB.load("Tetris.gb");
	Memory memory;
	memory.dump();
}
