//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_HITBOX_H
#define JJBA_HITBOX_H

#include <SDL_rect.h>

class Hitbox {
private:
    SDL_Rect mBounds;
public:
    //Constructor
    Hitbox(const SDL_Rect &bounds);

    Hitbox(int x, int y, int width, int height);

    //Getters and setters
    const SDL_Rect &getBounds() const;

    void setPosition(int x, int y);

    void setBounds(const SDL_Rect &bounds);

    void setBounds(int x, int y, int width, int height);
};

#endif //JJBA_HITBOX_H
