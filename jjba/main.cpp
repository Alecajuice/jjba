#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL_image.h>

#include "gameName.h"

#include "hitbox.h"
#include "game.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//Initialize SDL
bool init();

//Load media
bool loadMedia();

//Free media and close SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = nullptr;

//Renderer
SDL_Renderer *gRenderer = nullptr;

//The surface contained by the window
SDL_Surface *gScreenSurface = nullptr;

//The image we will load and show on the screen
SDL_Surface *gHelloWorld = nullptr;

int main(int argc, char *args[]) {
    //Turn off stdout buffering for debugging
    setbuf(stdout, nullptr);

    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Create game
            Game *game = new Game(gRenderer);

            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Main loop
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render
                game->render(gRenderer);

                //Update screen
                SDL_RenderPresent(gRenderer);
//                //Apply the image
//                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
//
//                //Update the surface
//                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

bool init() {
    //Init success flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window with random name
        char *gameName = chooseGameName();
        printf(gameName);
        gWindow = SDL_CreateWindow(gameName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        delete gameName;

        if (gWindow == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP("assets/img/hello_world.bmp");
    if (gHelloWorld == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp",
               SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    //Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = nullptr;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

