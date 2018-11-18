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
    Object();

    explicit Object(const Hitbox &mHitbox);

    virtual void loadMedia(SDL_Renderer* renderer) = 0;

    const Hitbox &getMHitbox() const;

    void setMHitbox(const Hitbox &mHitbox);

    Spritesheet &getMSprites();

    void setMSprites(const Spritesheet &mSprites);

};

#endif //JJBA_OBJECT_H
