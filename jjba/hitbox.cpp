//
// Created by aleca on 11/17/2018.
//

#include "hitbox.h"

Hitbox::Hitbox(const SDL_Rect &bounds) : mBounds({0, 0, 0, 0}) {}

Hitbox::Hitbox(int x, int y, int width, int height) : mBounds({x, y, width, height}) {}

const SDL_Rect &Hitbox::getBounds() const {
    return mBounds;
}

void Hitbox::setPosition(int x, int y) {
    Hitbox::mBounds = {x, y, Hitbox::mBounds.w, Hitbox::mBounds.h};
}

void Hitbox::setBounds(const SDL_Rect &bounds) {
    Hitbox::mBounds = bounds;
}

void Hitbox::setBounds(int x, int y, int width, int height) {
    Hitbox::mBounds = {x, y, width, height};
}



