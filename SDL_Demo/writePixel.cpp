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

    while (!quit){
        SDL_UpdateTexture(texture, NULL, pixels, sHEIGHT * sizeof(uint32_t));
        SDL_WaitEvent(&sdlEvent);

        switch(sdlEvent.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = true;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_LEFT){
                    color = COLOR1;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_DOWN){
                    color = COLOR2;
                }
                else if(sdlEvent.key.keysym.sym == SDLK_RIGHT){
                    color = COLOR3;
                }
                else if (sdlEvent.key.keysym.sym == SDLK_UP){
                    refresh();
                }
                break;
            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown){
                    int mouseX = sdlEvent.motion.x;
                    int mouseY = sdlEvent.motion.y;
                    pixels[mouseY * sHEIGHT + mouseX] = color;
                }
            break;
        }
        SDL_RenderClear(renderma);
        SDL_RenderCopy(renderma, texture, NULL, NULL);
        SDL_RenderPresent(renderma);
    }
        // printPix();
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderma);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void printPix(){
    for (int i = 0; i < sHEIGHT; i++){
        for (int j = 0; j < sWIDTH; j++){
            // if (sWIDTH % j == 0) printf("\n");
            printf("%08x ", pixels[j*sHEIGHT+i]);
        }
    }
    printf("\n\n\n\n");
}

void refresh(){
    for (int i = 0; i < sHEIGHT; i++)
    {
        for (int j = 0; j < sWIDTH; j++)
        {
            pixels[j * sHEIGHT + i] = COLOR0;
        }
    }
}