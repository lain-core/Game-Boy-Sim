// Memory.h
// Authors: Joe Story, Hunter King
#ifndef PPUnit_H
#define PPUnit_H 
#include <cstdint> //fixed-width unsigned ints
#include "Sim.h"
#include <SDL2/SDL.h>
#include "Memory.h"

class PPUnit{
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Texture *texture;
    uint32_t tileRowArray[TILE_WIDTH] = {0};
    uint32_t sdlPix[(GB_WIDTH * GB_HEIGHT)] = {0};
    Memory * memory;


public:
    PPUnit();
    ~PPUnit();
    void addMem(Memory *);
    void getRowColor(uint16_t);
    void render_tiles();
    void scan_line();
    void updateSDL();
    void refresh();
    }; //End class PPUnit
#endif
