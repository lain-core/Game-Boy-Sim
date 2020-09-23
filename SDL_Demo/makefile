CC = g++
CFLAGS = -g -c -Wall -std=c++11 -0g
OBJ = SDL_Demo.o SDL_keyInput.o

INCLUDE_PATHS =	-IC:\mingw_dev_lib\include\SDL2
LIBRARY_PATHS =	-LC:\mingw_dev_lib\lib
COMPILER_FLAGS = -w -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

.cpp.o:
	$(CC) $(FLAGS) $< -o $@

sdl: $(OBJ)

SDL_Demo.o:

SDL_keyInput.o:	

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(sdl)

clean:
	rm $(OBJ) sdl || true

run:
	make clean

# # Directories
# S_DIR=source
# B_DIR=build

# # Files
# S_FILES=$(S_DIR)/sdl_test.cpp

# # Output
# EXEC=$(B_DIR)/sdl_app

# # Build settings
# CC=g++
# # SDL options
# CC_SDL=-lSDL `sdl-config --cflags --libs`


# all:Build

# Build:
#   $(CC) $(S_FILES) -o $(EXEC) $(CC_SDL)

# build_run:Build
#   $(EXEC)

# clean:
#   rm -rf $(B_DIR)/*