#include <utility>
#include <fstream>

//
// Created by aleca on 11/18/2018.
//

#include "spritesheet.h"

const int FPS_DEFAULT = 30;

Spritesheet::Spritesheet() = default;

Spritesheet::Spritesheet(SDL_Renderer *renderer, std::string path, Uint8 keyR, Uint8 keyG, Uint8 keyB) {
    loadFromFile(renderer, std::move(path), keyR, keyG, keyB);
}

bool Spritesheet::loadFromFile(SDL_Renderer *renderer, std::string path, Uint8 keyR, Uint8 keyG, Uint8 keyB) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture *newTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load((path + ".png").c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", (path + ".png").c_str(), IMG_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, keyR, keyG, keyB));

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

void Spritesheet::render(SDL_Renderer *renderer, SDL_Rect bounds, SDL_RendererFlip flipType, SDL_Rect *clip) {
    //Render to screen
    SDL_RenderCopyEx(renderer, mTexture, clip, &bounds, 0, nullptr, flipType);
}

void Spritesheet::render(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_RendererFlip flipType,
                         SDL_Rect *clip) {
    render(renderer, {x, y, width, height}, flipType, clip);
}

nlohmann::json getFrameValue(nlohmann::json animation, int curFrame, std::string key) {
    if (animation["frames"][curFrame][key] == nullptr) {
        return animation["default"][key];
    } else {
        return animation["frames"][curFrame][key];
    }
}

void Spritesheet::render(SDL_Renderer *renderer, SDL_Rect hitbox, std::string animationName, Uint32 startTime,
                         SDL_RendererFlip flipType, int fps) {
    //IDLE: hitbox width: 56, height: 110

    //Store animation data in variable
    nlohmann::json animation = (mFrames)[animationName];

    //Calculate current frame from game time
    int numFrames = (int) animation["length"];
    int framesPerSecond;
    if (fps != -1) {
        framesPerSecond = fps;
    } else if (animation["fps"] != nullptr) {
        framesPerSecond = animation["fps"];
    } else {
        framesPerSecond = FPS_DEFAULT;
    }
    int curTime = SDL_GetTicks();
    int curFrame = ((curTime - startTime) * framesPerSecond / 1000) % numFrames;

    //If animation sprites have static widths, calculate x from widths
    int x;
    if (animation["variable_width"]) {
        x = getFrameValue(animation, curFrame, "x");
    } else {
        int xVal = getFrameValue(animation, curFrame, "x");
        int wVal = getFrameValue(animation, curFrame, "width");
        x = xVal + curFrame * wVal;
    }

    //Construct clipping rectangle
    int yVal = getFrameValue(animation, curFrame, "y");
    int wVal = getFrameValue(animation, curFrame, "width");
    int hVal = getFrameValue(animation, curFrame, "height");
    SDL_Rect clip = {x, yVal, wVal, hVal};

    //Construct bounds rectangle
    int xOffsetVal = getFrameValue(animation, curFrame, "x-offset");
    int yOffsetVal = getFrameValue(animation, curFrame, "y-offset");
    SDL_Rect bounds;
    if (flipType == SDL_FLIP_HORIZONTAL) {
        bounds = {hitbox.x + hitbox.w - xOffsetVal - wVal, hitbox.y + yOffsetVal, wVal, hVal};
    } else {
        bounds = {hitbox.x + xOffsetVal, hitbox.y + yOffsetVal, wVal, hVal};
    }

    //Render
    render(renderer, bounds, flipType, &clip);
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

bool Spritesheet::animationDone(std::string animationName, Uint32 startTime, int fps) {
    //Store animation data in variable
    nlohmann::json animation = (mFrames)[animationName];

    //Calculate current frame from game time
    int numFrames = (int) animation["length"];
    int framesPerSecond;
    if (fps != -1) {
        framesPerSecond = fps;
    } else if (animation["fps"] != nullptr) {
        framesPerSecond = animation["fps"];
    } else {
        framesPerSecond = FPS_DEFAULT;
    }
    int curTime = SDL_GetTicks();
    int curFrame = (curTime - startTime) * framesPerSecond / 1000;
    return curFrame >= numFrames;
}

