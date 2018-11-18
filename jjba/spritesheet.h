//
// Created by aleca on 11/18/2018.
//

#ifndef JJBA_SPRITESHEET_H
#define JJBA_SPRITESHEET_H

#include <SDL_render.h>
#include <string>

class Spritesheet {
private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
public:
    //Constructors
    Spritesheet();
    explicit Spritesheet(std::string path);

    //Load texture from file
    void loadFromFile(std::string path);

    //Render
    void render(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Rect* clip = NULL);
    void render(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Rect* clip = NULL);

    //Free texture
    void free();
};

#endif //JJBA_SPRITESHEET_H
