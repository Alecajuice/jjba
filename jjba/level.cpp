#include <utility>

#include <utility>

//
// Created by aleca on 1/4/2019.
//

#include "level.h"

Level::Level() : Object() {}

Level::Level(std::vector<Hitbox> mHitboxes) : Object({0, 0}, std::move(mHitboxes)){}

Level::Level(std::string source) : Object() {
    mPosition = {0, 0};
    loadFromSource(std::move(source));
}

void Level::loadFromSource(std::string source) {

}

void Level::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    for (auto hitbox : mHitboxes) {
        hitbox.setPosition({hitbox.getX() + mPosition.x, hitbox.getY() + mPosition.y});
        SDL_Rect rect = hitbox.getSDL_Rect();
        SDL_RenderDrawRect(renderer, &rect);
    }
}
