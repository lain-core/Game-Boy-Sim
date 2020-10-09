CC = g++
CFLAGS = -g -c -Wall -std=c++17 -Og
INSTDIR = Instructions
OBJ = Tools.o Memory.o GBLoader.o Registers.o Pixel.o Decode.o gb.o
INST_OBJ = $(INSTDIR)/Misc.o $(INSTDIR)/Arithmetic.o $(INSTDIR)/BitOps.o

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

gb: $(OBJ) $(INST_OBJ)

Decode.o: gb.h Sim.h

Tools.o: Tools.h

Memory.o: Memory.h Sim.h

Registers.o: Registers.h Sim.h

GBLoader.o: gb.h

Pixel.o: Sim.h Pixel.h

$(INSTDIR)/Misc.o: gb.h Sim.h

$(INSTDIR)/BitOps.o: gb.h Sim.h

$(INSTDIR)/Arithmetic.o: gb.h Tools.h Sim.h

gb.o: Tools.h Memory.h Registers.h Pixel.h

clean:
	rm $(OBJ) gb || true

run:
	make clean
