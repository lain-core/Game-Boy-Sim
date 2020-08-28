CC = g++
CFLAGS = -g -c -Wall -std=c++11 -Og
OBJ = Tools.o Memory.o gb.o

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

gb: $(OBJ)

Tools.o: Tools.h

Memory.o: Tools.h Memory.h Sim.h

gb.o: Tools.h Memory.h Sim.h

clean:
	rm $(OBJ) GB || true

run:
	make clean