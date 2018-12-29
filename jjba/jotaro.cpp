//
// Created by aleca on 11/17/2018.
//

#include "jotaro.h"

Jotaro::Jotaro() : StandUser(Hitbox(300, 300, 56, 110), Hitbox(300, 300, 104, 107)){

}

void Jotaro::loadMedia(SDL_Renderer* renderer) {
    //Color key image to #8080ff
    setMSprites(Spritesheet(renderer, "assets/spritesheets/JotaroKujo", 0x80, 0x80, 0xFF));
    setMAnimationStartTime(SDL_GetTicks());
}

void Jotaro::render(SDL_Renderer *renderer) {
    StandUser::render(renderer);
}

const int Jotaro::getMoveSpeed() const {
    return 300;
}

const int Jotaro::getStandMoveSpeed() const {
    return 600;
}
