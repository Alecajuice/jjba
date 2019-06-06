#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL_image.h>
//#include <afxres.h>

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

//Game Controller 1 handler
SDL_GameController *gGameController = nullptr;

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

            //Timestep variables
//            double t = 0.0;
            const double dt = 1000 / 60.0; //60 fps
            double currentTime = SDL_GetTicks();

            //Main loop
            while (!quit) {
                //Update timestep
                double newTime = SDL_GetTicks();
                double frameTime = newTime - currentTime;
                currentTime = newTime;

                while (frameTime > 0.0) {
                    const double deltaTime = std::min(frameTime, dt);
                    quit = game->update(deltaTime, gGameController);
                    frameTime -= deltaTime;
//                    t += deltaTime;
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

            delete game;
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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window with random name
        char *gameName = chooseGameName();
        printf("%s\n", gameName);
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
                //Check for joysticks
                if (SDL_NumJoysticks() < 2) {
                    printf("Warning: No joysticks connected!\n");
                } else {
                    printf("Number of joysticks connected: %d\n", SDL_NumJoysticks());
                    //Load joystick
                    gGameController = SDL_GameControllerOpen(0);
                    if (gGameController == nullptr) {
                        printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
                    }
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

    //Close game controller
    SDL_GameControllerClose(gGameController);
    gGameController = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

