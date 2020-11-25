// PPUnit.cpp
// Authors: Hunter King, Joe Story

#include <iostream>
#include <iomanip>
#include <SDL2/SDL.h>
#include "Sim.h"
#include "PPUnit.h"

SDL_Window *window;
SDL_Renderer *render;
SDL_Texture *texture;

PPUnit::PPUnit(){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Game Boy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GB_WIDTH, GB_HEIGHT, 0);
    render = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, GB_WIDTH, GB_HEIGHT);
}

PPUnit::~PPUnit(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void PPUnit::addMem(Memory * arg_memory){
    memory = arg_memory;
}

/*
 * getRowColor
 * Given two bytes, returns a pointer to an array of 8 pixel color values as expected by SDL2 (ARGB_8888 / uint32_t).
 * For example, the tile 0x5030 will return: [COLOR0, COLOR1, COLO2, COLOR3, COLOR0, COLOR0, COLOR0, COLOR0] where COLORX is macro'd in Sim.h.
 */
void PPUnit::getRowColor(uint16_t row){
    uint8_t vramRow[8] = {0};
    uint16_t byte1 = (row & 0xFF00) >> 8; // grab high order byte out of the 2
    uint16_t byte2 = (row & 0x00FF);      // grab low order byte
    uint16_t mask = 0x01;
    refresh();

    std::cout << "our row is: 0x" << std::hex << row << std::endl;
    std::cout << "our byte1 is: 0x" << std::hex << byte1 << std::endl;
    std::cout << "our byte2 is: 0x" << std::hex << byte2 << std::endl;

    for (int i = 0; i < 8; i++){
            if (byte1 & (mask << i)) vramRow[7-i] += 1; // if byte 1's bit is on
            if (byte2 & (mask << i)) vramRow[7-i] += 2; // if byte 2's bit is on
    }
    
    for (int i = 0; i < 8; i++){
        switch(vramRow[i])
        {
        case 0:
            tileRowArray[i] = COLOR0;
            break;

        case 1:
            tileRowArray[i] = COLOR1;
            break;

        case 2:
            tileRowArray[i] = COLOR2;
            break;

        case 3:
            tileRowArray[i] = COLOR3;
            break;
        default:
            break;
        }
    }
}

/*
 * scan_line()
 * render one scan line.
 */
void PPUnit::scan_line(){
    uint8_t control = memory->getByte(LCD_CONTROL);
    uint8_t test = 1;
    if(control & (test << BG_DISPLAY)) render_tiles();
    //if(control & (test << OBJ_DISPLAY)) render_sprites;
}

void PPUnit::render_tiles(){
// where to draw the visual area and the window
   uint8_t scrollY = memory->getByte(SCROLL_Y);
   uint8_t scrollX = memory->getByte(SCROLL_X);
   uint8_t windowY = memory->getByte(WINDOW_Y);
   uint8_t windowX = memory->getByte(WINDOW_X) - 7;
//    printf("ScrollY: %02x\n", memory->getByte(SCROLL_Y));
    uint8_t positionY = 0; // used to calculate current scanline
    uint8_t positionX = 0; // used in pixel writing loop
    uint16_t tileData = 0;
    uint16_t bgData = 0;
    bool is_unsigned = true;
    bool inWindow = false;

    // if the window is enabled
    if (WIN_DISPLAY_ENABLE){
        // if the current scanline is within the windows y-position
        if (windowY <= memory->getByte(LY)){
            // then we are using the window
            inWindow = true;
        }
    }

    // this block finds which tile data we are using
    if (GB_WINDOW_SELECT){
        tileData = VRAM; // VRAM is 0x8000
        is_unsigned = false;
    } 
    else tileData = 0x8800;

    // this block finds which background data we are using
    if (inWindow){
        positionY = memory->getByte(LY) + scrollY; // if we are in the window set current bounds, if we are outside fix it
        if (BG_MAP_SELECT) bgData = 0x9C00;
        else bgData = 0x9800;
    }
    else {
        positionY = memory->getByte(LY) - windowY;
    }


   // draw 160 pixels on this scanline
   //However, we ARE grabbing an entire tile row so this only needs to run 20x.
   //FIXME: 20 * 18 is equal to Number of tiles wide X number of tiles high, but this is ugly.
   for (int i = 0; i < 20; i++){
        positionX = i + scrollX;
        printf("posX: %d\n", positionX);
        // translate the current positionX to window space if necessary
        if (inWindow && i >= windowX) positionX = i - windowX;

        printf("in Window posX: %d\n", positionX);


        // find which of the 8 tile scanlines we are on
        uint16_t tileRow = (((uint16_t) (positionY/8))*32);
        // which tile does the positionX fall within
        uint16_t tileCol = positionX / 8;
        int16_t tileNum;
        uint16_t tileAddress = bgData + tileRow + tileCol;
        // what tile are we in, either signed or unsigned
        //FIXME: not sure if we need the cast on the unsigned
        if (is_unsigned) tileNum = (uint8_t) memory->getByte(tileAddress);
        else tileNum = (int8_t) memory->getByte(tileAddress);

        // find where this tile id is in memory
        uint16_t tileLocation = tileData;
        if (is_unsigned) tileLocation += (tileNum * 16);
        else tileLocation += ((tileNum + 128) * 16);

        //For example, if we have our sample tile ROW 0x5030.
        /*uint16_t tilepiece = memory->getTileRow(tileLocation);
        uint32_t * row;
        getRowColor(tilepiece);
        for(int j = 0; j < 8; j++){
            printf("Color %d: %08x\n", j, tileRowArray[j]);
        }*/
        for(int j = 0; j < 8; j++){
            uint16_t tilepiece = memory->getTileRow(tileLocation + (j*2));
            printf("tilepiece: %04x\n\n", tilepiece);
            getRowColor(tilepiece);
            for(int k = 0; k < 8; k++){
                printf("Color %d for row %d is: %08x\n", k, j, tileRowArray[k]);
            }
        }
   }
        updateSDL();

}

void PPUnit::updateSDL(){
    bool quit = false;
    //SDL_Event event;
    printf("attempting to accesss lcdArray.\n");


    for (int i = 0; i < TILE_WIDTH; i++){
        sdlPix[i] = tileRowArray[i];
    }
    while(!quit){
        SDL_UpdateTexture(texture, NULL, sdlPix, GB_WIDTH * sizeof(uint32_t));
        SDL_RenderClear(render);
        SDL_RenderCopy(render, texture, NULL, NULL);
        SDL_RenderPresent(render);
    }
}

void PPUnit::refresh(){
    //Clean up our tileRowArray before parsing in another tile.
    for(int i = 0; i < TILE_WIDTH; i++){
        tileRowArray[i] = 0;
    }
}