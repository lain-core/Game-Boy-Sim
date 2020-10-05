#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>

#define COLOR0 0x000f380f 
#define COLOR1 0x00306230 
#define COLOR2 0x008bac0f 
#define COLOR3 0x009bbc0f 

uint32_t miniPix[8];
uint32_t pixels;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

uint32_t rmask = 0xff000000;
uint32_t gmask = 0x00ff0000;
uint32_t bmask = 0x0000ff00;
uint32_t amask = 0x000000ff;

void init();
// void loadMedia();
uint32_t * getRowColor(uint16_t row);
void smiley();


SDL_Window* window = NULL;
SDL_Renderer* renderma = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* stretchedSurface = NULL;
SDL_Texture* texture = NULL;


void init(){
    // initialize sdl
    SDL_Init(SDL_INIT_VIDEO); 
    //create the window
    window = SDL_CreateWindow("PLEASE WORK", SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
                            SDL_WINDOW_SHOWN);
    renderma = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // screenSurface = SDL_GetWindowSurface(window);
//     texture = SDL_CreateTexture(renderma, SDL_PIXELFORMAT_ABGR8888, 
//                             SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}

// void loadMedia(){
  
// }

int main(){
    bool quit = false;
    SDL_Event e;

    init();
    smiley();
    // loadMedia();

    while(!quit){
        while(SDL_PollEvent(&e)!=0){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            // else if (e.type == SDL_KEYDOWN ) {
            //     switch(e.key.keysym.sym){
            //         case SDLK_UP:
    
            //             break();
            //         default:
            //             break();
            //     }
            // }
        }
        SDL_SetRenderDrawColor(renderma, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderma);

        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(stretchedSurface, NULL, screenSurface, &stretchRect);
        SDL_UpdateWindowSurface(window);
    }
}

uint32_t * getRowColor(uint16_t row){
    for (int i = 0; i < 8; i++){
        miniPix[i] = -1;
    }
        uint16_t byte1 = (row & 0xFF00) >> 8; // grab high order byte out of the 2
        uint16_t byte2 = (row & 0x00FF);      // grab low order byte
        uint16_t mask = 0x01;

        for (int i = 0; i < 8; i++){
            if (byte1 & (mask << i)) miniPix[7-i] += 2; // if byte 1's bit is on
            if (byte2 & (mask << i)) miniPix[7-i] += 3; // if byte 2's bit is on
            switch (miniPix[7-i]){
            case 0:
                miniPix[7-i] = COLOR0;
                break;

            case 1:
                miniPix[7-i] = COLOR1;
                break;

            case 2:
                miniPix[7-i] = COLOR2;
                break;

            case 3:
                miniPix[7-i] = COLOR3;
                break;

            default:
                miniPix[7-i] = 0x00000000;
                break;
            }
        }
        return miniPix;
}

void smiley(){
    uint32_t **pixels = (uint32_t **)malloc(8 * sizeof(uint32_t *));
    for (int i = 0; i < 8; i++)
    {
        pixels[i] = (uint32_t *)malloc(8 * sizeof(uint32_t));
    }


    uint16_t smileyTile[8] = {0xFF00, 0xFF00, 0xFF24, 0xFF00,
                              0xFF42, 0xFF7E, 0xFF00, 0xFF00};

    for (int i = 0; i < 8; i++)
    {
        pixels[i] = getRowColor(smileyTile[i]);
        // for (int j = 0; j < 8; j++)
        //     printf("% 6x ", pixels[i][j]);
        // printf("\n");
    }

    screenSurface = SDL_CreateRGBSurfaceFrom((void*) pixels, SCREEN_WIDTH, SCREEN_HEIGHT, 4, 1, rmask, gmask, bmask, amask); 
}
