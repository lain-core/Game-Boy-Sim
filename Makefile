CC = g++
CFLAGS = -g -c -Wall -std=c++11 -Og
OBJ = Tools.o Memory.o GBLoader.o gb.o

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

gb: $(OBJ)

Tools.o: Tools.h

Memory.o: Tools.h Memory.h Sim.h

GBLoader.o: gb.h GBLoader.h

gb.o: Tools.h Memory.h 

clean:
	rm $(OBJ) gb || true

run:
	make clean
