//
// Created by aleca on 11/18/2018.
//
#include <SDL2/SDL_image.h>

#include "spritesheet.h"

Spritesheet::Spritesheet() = default;

Spritesheet::Spritesheet(std::string path) {

}

void Spritesheet::loadFromFile(std::string path) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture *newTexture = nullptr;
    
    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    }
}

void Spritesheet::render(SDL_Renderer *renderer, SDL_Rect bounds, SDL_Rect *clip) {
    //Render to screen
    SDL_RenderCopy(renderer, mTexture, clip, &bounds);
}

void Spritesheet::render(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Rect *clip) {
    render(renderer, {x, y, width, height}, clip);
}

void Spritesheet::free() {

}
