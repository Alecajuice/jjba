//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_OBJECT_H
#define JJBA_OBJECT_H

#include "hitbox.h"
#include "spritesheet.h"

class Object {
private:
    Hitbox mHitbox;
    SDL_Point mVelocity;

    Spritesheet mSprites;
public:
    void loadMedia();
};

#endif //JJBA_OBJECT_H
