/*

    THIS HAS BEEN ADAPTED FROM A DEMO ON dzone.com

*/


#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

#define COLOR0 0x000f380f
#define COLOR1 0x00306230
#define COLOR2 0x008bac0f
#define COLOR3 0x009bbc0f

uint32_t *pixels;
uint32_t *miniPix;
void printPix();
uint32_t *getRowColor(uint16_t row);
void smiley();
void scalePixArray();
void initPixArray();
void initMiniPixArray();

int screenHEIGHT = 0;
int screenWIDTH = 0;
int tileHEIGHT = 0;
int tileWIDTH = 0;
int scaleHEIGHT = 0;
int scaleWIDTH =0;

int main(int argc, char **argv)
{
    bool quit = false;
    screenHEIGHT = 640;
    screenWIDTH = 480;
    tileHEIGHT = 8;
    tileWIDTH = 8;
    scaleHEIGHT = screenHEIGHT / tileHEIGHT;
    scaleWIDTH = screenWIDTH / tileWIDTH;

    SDL_Event sdlEvent;
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Dzone Example", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenHEIGHT, screenWIDTH, 0);

    SDL_Renderer * renderma = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture * texture = SDL_CreateTexture(renderma,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, screenHEIGHT, screenWIDTH);

    initPixArray();
    initMiniPixArray();
    // memset(pixels, COLOR1, screenHEIGHT * screenWIDTH * sizeof(uint32_t));
    smiley();

    while (!quit){
        SDL_UpdateTexture(texture, NULL, pixels, screenHEIGHT * sizeof(uint32_t));
        SDL_WaitEvent(&sdlEvent);

        // switch(sdlEvent.type){
        switch(sdlEvent.key.keysym.scancode){
            case SDL_QUIT:
                quit = true;
                break;            
            case SDLK_UP:
                scalePixArray();
                break;
            case SDLK_DOWN:
                miniPix = new uint32_t[tileHEIGHT * tileWIDTH];
                for (int i = 0; i < tileHEIGHT; i++)
                {
                    for (int j = 0; j < tileWIDTH; j++)
                    {
                        miniPix[j * tileHEIGHT + i] = COLOR3;
                    }
                }
                break;
            case SDLK_LEFT:
                quit = true;
                break;
            // case SDL_MOUSEMOTION:
            //     int mouseX = sdlEvent.motion.x;
            //     int mouseY = sdlEvent.motion.y;
            //     pixels[mouseY * screenHEIGHT + mouseX] = COLOR3;
            //     break;
        }
        SDL_RenderClear(renderma);
        SDL_RenderCopy(renderma, texture, NULL, NULL);
        SDL_RenderPresent(renderma);
    }
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderma);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void printPix(){
    for (int i = 0; i < screenHEIGHT; i++){
        for (int j = 0; j < screenWIDTH; j++){
            // if (screenWIDTH % j == 0) printf("\n");
            printf("%08x ", pixels[j*screenHEIGHT+i]);
        }
    }
    printf("\n\n\n\n");
}

uint32_t *getRowColor(uint16_t row)
{
    for (int i = 0; i < 8; i++)
    {
        miniPix[i] = -1;
    }
    uint16_t byte1 = (row & 0xFF00) >> 8; // grab high order byte out of the 2
    uint16_t byte2 = (row & 0x00FF);      // grab low order byte
    uint16_t mask = 0x01;

    for (int i = 0; i < 8; i++)
    {
        if (byte1 & (mask << i))
            miniPix[7 - i] += 2; // if byte 1's bit is on
        if (byte2 & (mask << i))
            miniPix[7 - i] += 3; // if byte 2's bit is on
        switch (miniPix[7 - i])
        {
        case 0:
            miniPix[7 - i] = COLOR0;
            break;

        case 1:
            miniPix[7 - i] = COLOR1;
            break;

        case 2:
            miniPix[7 - i] = COLOR2;
            break;

        case 3:
            miniPix[7 - i] = COLOR3;
            break;

        default:
            miniPix[7 - i] = 0x00000000;
            break;
        }
    }
    return miniPix;
}

void smiley()
{
    uint16_t smileyTile[8] = {0xFF00, 0xFF00, 0xFF24, 0xFF00,
                              0xFF42, 0xFF7E, 0xFF00, 0xFF00};

    for (int i = 0; i < 8; i++)
    {
        miniPix[i] = *getRowColor(smileyTile[i]);
        // for (int j = 0; j < 8; j++)
        //     printf("%x ", pixels[i][j]);
        // printf("\n");
    }
}

void scalePixArray(){
    for (int i = 0 ; i < screenHEIGHT; i++){
        for (int j = 0; j < screenWIDTH; j++){
            pixels[j * tileHEIGHT + i] = miniPix[(j * tileHEIGHT + i)%8];
        }
    }
}

void initPixArray(){
    pixels = new uint32_t[screenHEIGHT * screenWIDTH];
    for (int i = 0; i < screenHEIGHT; i++)
    {
        for (int j = 0; j < screenWIDTH; j++)
        {
            // if ((j * screenHEIGHT + i) % 2 == 0)
            pixels[j * screenHEIGHT + i] = COLOR0;
            // else pixels[j * screenHEIGHT + i] = COLOR0;
        }
    }
}

void initMiniPixArray(){
    miniPix = new uint32_t[tileHEIGHT * tileWIDTH];
    for (int i = 0; i < tileHEIGHT; i++)
    {
        for (int j = 0; j < tileWIDTH; j++)
        {
            miniPix[j * tileHEIGHT + i] = COLOR0;
        }
    }
}