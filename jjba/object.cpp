//
// Created by aleca on 11/17/2018.
//

#include "object.h"

Object::Object() : mHitbox(0, 0, 0, 0), mVelocity({0, 0}) {}

Object::Object(const Hitbox &mHitbox) : mHitbox(mHitbox), mVelocity({0, 0}) {}

void Object::update(const double deltaTime) {
    mHitbox.translate(mVelocity.x * deltaTime / 1000, mVelocity.y * deltaTime / 1000);
}

Hitbox Object::getMHitbox() const {
    return mHitbox;
}

void Object::setMHitbox(const Hitbox &mHitbox) {
    Object::mHitbox = mHitbox;
}

const Vector &Object::getMVelocity() const {
    return mVelocity;
}

void Object::setMVelocity(const Vector &mVelocity) {
    Object::mVelocity = mVelocity;
}

void Object::setPosition(double x, double y) {
    mHitbox.setPosition(x, y);
}


SpriteObject::SpriteObject() : Object() {}

SpriteObject::SpriteObject(const Hitbox &mHitbox) : Object(mHitbox) {}

Uint32 SpriteObject::getMAnimationStartTime() const {
    return mAnimationStartTime;
}

SDL_RendererFlip SpriteObject::getMFlipType() const {
    return mFlipType;
}

void SpriteObject::setMFlipType(SDL_RendererFlip mFlipType) {
    SpriteObject::mFlipType = mFlipType;
}

void SpriteObject::setMAnimationStartTime(Uint32 mAnimationStartTime) {
    SpriteObject::mAnimationStartTime = mAnimationStartTime;
}

const Spritesheet &SpriteObject::getMSprites() const {
    return mSprites;
}

void SpriteObject::setMSprites(const Spritesheet &mSprites) {
    SpriteObject::mSprites = mSprites;
}

