//
// Created by aleca on 11/17/2018.
//

#include "object.h"

Object::Object() : mPosition({0, 0}), mVelocity({0, 0}) {
    mHitboxes.emplace_back(0, 0, 0, 0);
}

Object::Object(Vector position, const std::vector<Hitbox> mHitboxes) : mPosition(position), mVelocity({0, 0}), mHitboxes(mHitboxes) {}

Object::Object(double x, double y, const std::vector<Hitbox> mHitboxes) : mPosition({x, y}), mVelocity({0, 0}), mHitboxes(mHitboxes) {}

void Object::update(const double deltaTime) {
    mPosition.x += mVelocity.x * deltaTime / 1000;
    mPosition.y += mVelocity.y * deltaTime / 1000;
//    mHitbox.translate(mVelocity.x * deltaTime / 1000, mVelocity.y * deltaTime / 1000);
}

std::vector<Hitbox> Object::getMHitboxes() const {
    return mHitboxes;
}

void Object::setMHitboxes(const std::vector<Hitbox> mHitboxes) {
    Object::mHitboxes = mHitboxes;
}

const Vector &Object::getMVelocity() const {
    return mVelocity;
}

void Object::setMVelocity(const Vector &mVelocity) {
    Object::mVelocity = mVelocity;
}

void Object::setPosition(double x, double y) {
    mPosition.x = x;
    mPosition.y = y;
}

const Vector &Object::getMPosition() const {
    return mPosition;
}

void Object::setMPosition(const Vector &mPosition) {
    Object::mPosition = mPosition;
}


SpriteObject::SpriteObject() : Object() {}

SpriteObject::SpriteObject(Vector position, const std::vector<Hitbox> mHitboxes) : Object(position, mHitboxes) {}

SpriteObject::SpriteObject(double x, double y, const std::vector<Hitbox> mHitboxes) : Object(x, y, mHitboxes) {}

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

