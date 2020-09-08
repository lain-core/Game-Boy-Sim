#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

// key press surface constants
enum KeyPressSurfaces{
    KeyPressDEFAULT,
    KeyPressUP,
    KeyPressDOWN,
    KeyPressLEFT,
    KeyPressRIGHT,
    KeyPressTOTAL
};

bool init(); // creates a window

bool loadMedia(); 

void close(); // turns off media and sdl

SDL_Surface * loadSurface(std::string path);

SDL_Window * window = NULL;

SDL_Surface * screenSurface = NULL;

SDL_Surface * keyPressSurfaces[KeyPressTOTAL];

SDL_Surface * currentSurface = NULL;

bool init(){
    bool status = true;

    // would initilize SDL here but I am going to see if it will work without it

    window = SDL_CreateWindow("Gameboy Graphics Testing", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL){
        printf("Window was not created. ERROR: %s\n", SDL_GetError());
        status = false;
    }
    else {
        screenSurface = SDL_GetWindowSurface(window);
    }    

    return status;
}

// loads images for each key press enum and returns if successful
bool loadMedia(){
    bool status = true;
    keyPressSurfaces[KeyPressDEFAULT] = loadSurface("textures/borgar.bmp");
    if(keyPressSurfaces[KeyPressDEFAULT] == NULL) status = false;

    keyPressSurfaces[KeyPressUP] = loadSurface("textures/up.bmp");
    if(keyPressSurfaces[KeyPressUP] == NULL) status = false;

    keyPressSurfaces[KeyPressDOWN] = loadSurface("textures/down.bmp");
    if(keyPressSurfaces[KeyPressDOWN] == NULL) status = false;

    keyPressSurfaces[KeyPressLEFT] = loadSurface("textures/left.bmp");
    if(keyPressSurfaces[KeyPressLEFT] == NULL) status = false;

    keyPressSurfaces[KeyPressRIGHT] = loadSurface("textures/right.bmp");
    if(keyPressSurfaces[KeyPressRIGHT] == NULL) status = false;

    return status;
}

void close(){
    // Deallocate surfaces
    for (int i = 0; i < KeyPressTOTAL; i++){
        SDL_FreeSurface(keyPressSurfaces[i]);
        keyPressSurfaces[i] = NULL;
    }

    // destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    //quits the subsystem
    // SDL_QUIT;
}

SDL_Surface * loadSurface(std::string path){
    SDL_Surface * loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    return loadedSurface;
}

int main(){
    if (!init()) printf("Failed to initialize!\n");
    else {
        if (!loadMedia()) printf("Failed to load media!\n");
        else{
            bool quit = false;
            // event handler
            SDL_Event event;
            // sets the default current surface
            currentSurface = keyPressSurfaces[KeyPressDEFAULT]; 
            // while the application is running
            while(!quit){
                // while there are events on the queue
                while (SDL_PollEvent(&event) != 0){
                    //user requests to quit
                    if (event.type == SDL_QUIT) quit = true;
                    else if (event.type == SDL_KEYDOWN){    // user presses a key
                        switch(event.key.keysym.sym){
                            case SDLK_UP:
                            currentSurface = keyPressSurfaces[KeyPressUP];
                            break;

                            case SDLK_DOWN:
                            currentSurface = keyPressSurfaces[KeyPressDOWN];
                            break;

                            case SDLK_LEFT:
                            currentSurface = keyPressSurfaces[KeyPressLEFT];
                            break;

                            case SDLK_RIGHT:
                            currentSurface = keyPressSurfaces[KeyPressRIGHT];
                            break;

                            default:
                            currentSurface = keyPressSurfaces[KeyPressDEFAULT];
                            break;
                        }
                    }
                }
                // apply the current image
                SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);
                // update the surface
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    close();
    return 0;
}