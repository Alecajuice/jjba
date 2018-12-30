//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_OBJECT_H
#define JJBA_OBJECT_H

#include "hitbox.h"
#include "spritesheet.h"

class Object {
protected:
    Hitbox mHitbox;
    Vector mVelocity; //Velocity in pixels/second
public:
    //Constructors
    Object();

    explicit Object(const Hitbox &mHitbox);

    //Member functions
    virtual void update(double deltaTime);

    void setPosition(double x, double y);

    //Getters and setters
    Hitbox getMHitbox() const;

    void setMHitbox(const Hitbox &mHitbox);

    const Vector &getMVelocity() const;

    void setMVelocity(const Vector &mVelocity);

};

class SpriteObject : public Object {
private:
    Uint32 mAnimationStartTime;

    //Flip type
    SDL_RendererFlip mFlipType = SDL_FLIP_NONE;
protected:
    Spritesheet mSprites;
public:
    //Constructors
    SpriteObject();

    explicit SpriteObject(const Hitbox &mHitbox);

    //Member functions
    virtual void loadMedia(SDL_Renderer *renderer) = 0;

    //Getters and setters
    Uint32 getMAnimationStartTime() const;

    void setMAnimationStartTime(Uint32 mAnimationStartTime);

    SDL_RendererFlip getMFlipType() const;

    void setMFlipType(SDL_RendererFlip mFlipType);

    const Spritesheet &getMSprites() const;

    void setMSprites(const Spritesheet &mSprites);
};

#endif //JJBA_OBJECT_H
