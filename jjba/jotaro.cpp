//
// Created by aleca on 11/17/2018.
//

#include "jotaro.h"

Jotaro::Jotaro() : StandUser(Hitbox(0, 0, 76, 130)){

}

void Jotaro::loadMedia(SDL_Renderer* renderer) {
    setMSprites(Spritesheet(renderer, "assets/spritesheets/JotaroKujo"));
    getMSprites().setAnimationStartTime(SDL_GetTicks());
}

void Jotaro::render(SDL_Renderer *renderer) {
    getMSprites().render(renderer, getMHitbox().getBounds(), "IDLE");
}
