#include <SDL2/SDL.h>

#define WIDTH 160
#define HEIGHT 144

int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer * renderer; 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}