//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_OBJECT_H
#define JJBA_OBJECT_H

#include "hitbox.h"
#include "spritesheet.h"

class Object {
protected:
    Vector mPosition; //Position of center of motion
    Vector mPrevPosition; //Position last frame
    Vector mVelocity; //Velocity in pixels/second
    std::vector<Hitbox> mHitboxes;
public:
    //Constructors
    Object();

    Object(Vector position, std::vector<Hitbox> mHitboxes);

    Object(double x, double y, std::vector<Hitbox> mHitboxes);

    //Member functions
    virtual void update(double deltaTime);

    void setPosition(double x, double y);

    virtual Vector staticCollisionCheck(Object other); //Returns collision response vector

    //Getters and setters
    std::vector<Hitbox> getMHitboxes() const;

    void setMHitboxes(std::vector<Hitbox> mHitbox);

    const Vector &getMVelocity() const;

    void setMVelocity(const Vector &mVelocity);

    const Vector &getMPosition() const;

    void setMPosition(const Vector &mPosition);

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

    SpriteObject(Vector position, std::vector<Hitbox> mHitboxes);

    SpriteObject(double x, double y, std::vector<Hitbox> mHitboxes);

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
