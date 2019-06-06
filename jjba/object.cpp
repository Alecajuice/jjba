//
// Created by aleca on 11/17/2018.
//

#include "object.h"

Object::Object() : mPosition({0, 0}), mVelocity({0, 0}) {
    mHitboxes.emplace_back(0, 0, 0, 0);
}

Object::Object(Vector position, const std::vector<Hitbox> mHitboxes) : mPosition(position), mVelocity({0, 0}),
                                                                       mHitboxes(mHitboxes) {}

Object::Object(double x, double y, const std::vector<Hitbox> mHitboxes) : mPosition({x, y}), mVelocity({0, 0}),
                                                                          mHitboxes(mHitboxes) {}

void Object::update(const double deltaTime) {
    mPrevPosition = mPosition;
    mPosition.x += mVelocity.x * deltaTime / 1000;
    mPosition.y += mVelocity.y * deltaTime / 1000;
//    mHitbox.translate(mVelocity.x * deltaTime / 1000, mVelocity.y * deltaTime / 1000);
}

Vector Object::staticCollisionCheck(Object other) {
    Vector response = {0, 0};
    auto *overlap = new Vector;
    for (auto h1 : mHitboxes) {
        for (auto h2 : other.getMHitboxes()) {
            Hitbox h1Abs = h1.translate(mPosition);
            Hitbox h2Abs = h2.translate(other.getMPosition());
            if (checkCollision(h1Abs, h2Abs, overlap)) {
//                printf("h1\nx: %lf\ny: %lf\nw: %lf\nh: %lf\n", h1Abs.getX(), h1Abs.getY(), h1Abs.getW(), h1Abs.getH());
//                printf("h2\nx: %lf\ny: %lf\nw: %lf\nh: %lf\n", h2Abs.getX(), h2Abs.getY(), h2Abs.getW(), h2Abs.getH());
//                printf("x: %lf\ny: %lf\n", overlap->x, overlap->y);
                //Collision response
                bool xPrevOverlap = oneDimOverlap(h1.translate(mPrevPosition).getX(), h1.getW(),
                                                  h2.translate(other.getMPosition()).getX(), h2.getW());
                bool yPrevOverlap = oneDimOverlap(h1.translate(mPrevPosition).getY(), h1.getH(),
                                                  h2.translate(other.getMPosition()).getY(), h2.getH());
                if ((!xPrevOverlap && yPrevOverlap) ||
                    (!xPrevOverlap && fabs(overlap->x) <= fabs(overlap->y))) {
                    mPosition.x += overlap->x;
                    response.x += overlap->x;

                    if (overlap->x < 0) {
                        mVelocity.x = fmin(mVelocity.x, 0);
                    } else {
                        mVelocity.x = fmax(mVelocity.x, 0.0f);
                    }
                } else {
                    mPosition.y += overlap->y;
                    response.y += overlap->y;

                    if (overlap->y < 0) {
                        mVelocity.y = fmin(mVelocity.y, 0);
                    } else {
                        mVelocity.y = fmax(mVelocity.y, 0.0f);
                    }
                }
            }
        }
    }
    delete overlap;
    return response;
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

