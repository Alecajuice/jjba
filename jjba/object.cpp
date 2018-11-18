//
// Created by aleca on 11/17/2018.
//

#include "object.h"

const Hitbox &Object::getMHitbox() const {
    return mHitbox;
}

void Object::setMHitbox(const Hitbox &mHitbox) {
    Object::mHitbox = mHitbox;
}

Spritesheet &Object::getMSprites() {
    return mSprites;
}

void Object::setMSprites(const Spritesheet &mSprites) {
    Object::mSprites = mSprites;
}

Object::Object() : mHitbox(0, 0, 0, 0), mVelocity({0, 0}) {}

Object::Object(const Hitbox &mHitbox) : mHitbox(mHitbox), mVelocity({0, 0}) {}

