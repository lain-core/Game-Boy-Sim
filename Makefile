CC = g++
CFLAGS = -g -c -Wall -std=c++17 -Og
INSTDIR = Instructions
OBJ = Tools.o Memory.o GBLoader.o Registers.o Decode.o gb.o #PPUnit.o  
INST_OBJ = $(INSTDIR)/Misc.o $(INSTDIR)/Arithmetic.o $(INSTDIR)/BitOps.o $(INSTDIR)/BitShift.o $(INSTDIR)/Load.o $(INSTDIR)/Stack.o $(INSTDIR)/Jump.o 
SUBDIRS = asm
#MAC_SDL = -F/Library/Frameworks -framework SDL2
#LINUX_SDL = `pkg-config --cflags --libs` #sdl2
PLATFORM := $(shell uname)

# ifeq ($(PLATFORM),Darwin)
#     SDL = $(MAC_SDL)
# endif

# ifeq ($(PLATFORM),Linux)
#     SDL = $(LINUX_SDL)
# endif

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

gb: $(OBJ) $(INST_OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(INST_OBJ) $(SDL) -o gb

Decode.o: gb.h Sim.h Tools.h

Tools.o: Tools.h

Memory.o: Memory.h Sim.h

Registers.o: Registers.h Sim.h

GBLoader.o: gb.h

#PPUnit.o: Sim.h Memory.h PPUnit.h

$(INSTDIR)/Misc.o: gb.h Sim.h

$(INSTDIR)/BitOps.o: gb.h Sim.h

$(INSTDIR)/Arithmetic.o: gb.h Sim.h

$(INSTDIR)/Load.o: gb.h Sim.h

$(INSTDIR)/BitShift.o: gb.h Sim.h

$(INSTDIR)/Jump.o: gb.h Sim.h

$(INSTDIR)/Stack.o: gb.h Sim.h

gb.o: Tools.h Memory.h Registers.h #PPUnit.h

$(SUBDIRS):
	$(MAKE) -C $@ clean
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)

clean:
	rm $(OBJ) $(INST_OBJ) *.out gb || true

run:
	make clean
