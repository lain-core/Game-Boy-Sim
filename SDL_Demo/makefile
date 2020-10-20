CC = g++
CFLAGS = -g -Wall -std=c++17
MAC_SDL = -F/Library/Frameworks -framework SDL2
LINUX_SDL = `pkg-config --cflags --libs sdl2`
WIN_SDL = uhh_idk
PLATFORM := $(shell uname)
OBJ = pixelmod.o

ifeq ($(PLATFORM),Darwin)
    SDL = $(MAC_SDL)
endif

ifeq ($(PLATFORM),Linux)
    SDL = $(LINUX_SDL)
endif

pixelmod:
	$(CC) $(CFLAGS) pixelmod.cpp -o pixelmod $(SDL)

write:
	$(CC) $(CFLAGS) writePixel.cpp -o writePixel $(SDL)

clean:
	rm $(OBJ) writePixel pixelmod keyInputTest a.out || true
