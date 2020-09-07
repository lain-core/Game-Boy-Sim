#include <SDL2/SDL.h>

int main(){
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("borgar", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 420, 600, 0);
    
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface * image = SDL_LoadBMP("borgar.bmp");
    // printf("\n\nERROR MESSAGE: %s\n\n", SDL_GetError());
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    while(!quit){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                break;
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
