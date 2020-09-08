#include <SDL2/SDL.h>

int main(){
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("borgar", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 420, 600, 0);
    
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface * image = SDL_LoadBMP("textures/borgar.bmp");
    
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    while(!quit){

        while(SDL_PollEvent(&event) != 0){
            SDL_WaitEvent(&event);
            if(event.type == SDL_QUIT){
                quit = true;
            }

             
        }
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void putPixelRGB(SDL_Renderer * renderer, int x, int y, unsigned char r, 
    unsigned char g, unsigned char b){
    SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
    }
