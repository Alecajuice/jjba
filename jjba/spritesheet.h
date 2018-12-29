//
// Created by aleca on 11/18/2018.
//

#ifndef JJBA_SPRITESHEET_H
#define JJBA_SPRITESHEET_H

#include <SDL_render.h>
#include <string>
#include <nlohmann/json.hpp>
#include <SDL2/SDL_image.h>

class Spritesheet {
private:
    SDL_Texture *mTexture = nullptr;
    nlohmann::json mFrames = nullptr;

    int mWidth;
    int mHeight;

public:
    //Constructors
    Spritesheet();

    explicit Spritesheet(SDL_Renderer *renderer, std::string path, Uint8 keyR, Uint8 keyG, Uint8 keyB);

    //Member functions
    bool loadFromFile(SDL_Renderer *renderer, std::string path, Uint8 keyR, Uint8 keyG, Uint8 keyB);

    void render(SDL_Renderer *renderer, SDL_Rect bounds, SDL_RendererFlip flipType, SDL_Rect *clip = nullptr);

    void render(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_RendererFlip flipType,
            SDL_Rect *clip = nullptr);

    void render(SDL_Renderer *renderer, SDL_Rect hitbox, std::string animationName, Uint32 startTime,
                SDL_RendererFlip flipType, int fps = -1);

    bool animationDone(std::string animationName, Uint32 startTime, int fps = -1);

    //Free texture
    void free();
};

#endif //JJBA_SPRITESHEET_H
