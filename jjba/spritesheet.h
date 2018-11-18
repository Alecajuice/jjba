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
    SDL_Texture* mTexture = nullptr;
    nlohmann::json mFrames = nullptr;

    int mWidth;
    int mHeight;

    Uint32 animationStartTime;
public:
    void setAnimationStartTime(Uint32 startTime);

public:
    //Constructors
    Spritesheet();
    explicit Spritesheet(SDL_Renderer* renderer, std::string path);

    //Load texture from file
    bool loadFromFile(SDL_Renderer* renderer, std::string path);

    //Render
    void render(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Rect* clip = nullptr);
    void render(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Rect* clip = nullptr);
    void render(SDL_Renderer* renderer, SDL_Rect bounds, std::string animationName);

    //Free texture
    void free();
};

#endif //JJBA_SPRITESHEET_H
