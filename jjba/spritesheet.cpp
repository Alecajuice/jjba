#include <utility>
#include <fstream>

//
// Created by aleca on 11/18/2018.
//

#include "spritesheet.h"

const int FPS_DEFAULT = 30;

Spritesheet::Spritesheet() = default;

Spritesheet::Spritesheet(SDL_Renderer *renderer, std::string path) {
    loadFromFile(renderer, std::move(path));
}

bool Spritesheet::loadFromFile(SDL_Renderer *renderer, std::string path) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture *newTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load((path + ".png").c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", (path + ".png").c_str(), IMG_GetError());
    } else {
        //Color key image to #8080ff
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x80, 0x80, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", (path + ".png").c_str(), SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Load frames json
    std::ifstream i(path + ".json");
    nlohmann::json j;
    i >> j;


    //Return success
    mTexture = newTexture;
    mFrames = j;
    return mTexture != nullptr && mFrames != nullptr;
}

void Spritesheet::render(SDL_Renderer *renderer, SDL_Rect bounds, SDL_Rect *clip) {
    //Render to screen
    SDL_RenderCopy(renderer, mTexture, clip, &bounds);
}

void Spritesheet::render(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Rect *clip) {
    render(renderer, {x, y, width, height}, clip);
}

void Spritesheet::render(SDL_Renderer *renderer, SDL_Rect bounds, std::string animationName) {
    nlohmann::json animation = (mFrames)[animationName];
    int numFrames = (int)animation["length"];
    int fps;
    if(animation["fps"] != nullptr) {
        fps = animation["fps"];
    } else {
        fps = FPS_DEFAULT;
    }
    int curTime = SDL_GetTicks();
    int curFrame = ((curTime - animationStartTime) * fps / 1000) % numFrames;
    SDL_Rect clip;
    if(animation["variable_width"]) {
        nlohmann::json frame = animation[animationName]["frames"][curFrame];
        clip = {frame["x"], frame["y"], frame["width"], frame["height"]};
    } else {
        nlohmann::json frame = animation["frame"];
        clip = {(int)frame["x"] + curFrame * (int)frame["width"], frame["y"], frame["width"], frame["height"]};
    }

    render(renderer, bounds, &clip);
}

void Spritesheet::free() {
//Free texture if it exists
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void Spritesheet::setAnimationStartTime(Uint32 startTime) {
    Spritesheet::animationStartTime = startTime;
}

