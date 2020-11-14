#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

#define COLOR0 0x000f380f
#define COLOR1 0x00306230
#define COLOR2 0x008bac0f
#define COLOR3 0x009bbc0f

uint32_t *pixels;
void printPix();
void refresh();
// uint32_t *getRowColor(uint16_t row);

int sHEIGHT = 640;
int sWIDTH = 480;
uint32_t color = COLOR1;

int main(int argc, char **argv)
{
    int cyclesNum = 0;
    bool quit = false;
    bool leftMouseButtonDown = false;
    SDL_Event sdlEvent;
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Pixel Writing", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sHEIGHT, sWIDTH, 0);

    SDL_Renderer * renderma = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture * texture = SDL_CreateTexture(renderma,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, sHEIGHT, sWIDTH);

    pixels = new uint32_t[sHEIGHT * sWIDTH];
    refresh();
    // memset(pixels, COLOR1, sHEIGHT * sWIDTH * sizeof(uint32_t));

    while (cycleNum < ){
        
    }
        // printPix();
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderma);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}