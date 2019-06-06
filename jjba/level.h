//
// Created by aleca on 1/4/2019.
//

#ifndef JJBA_LEVEL_H
#define JJBA_LEVEL_H

#include "object.h"

class Level : public Object {
public:
    Level();

    explicit Level(std::vector<Hitbox> mHitboxes);

    explicit Level(std::string source);

    //Member functions
    void loadFromSource(std::string source);

    void render(SDL_Renderer *renderer);
};

#endif //JJBA_LEVEL_H
