//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_JOTARO_H
#define JJBA_JOTARO_H

#include "standUser.h"

class Jotaro : public StandUser {
public:
    Jotaro();

    void loadMedia(SDL_Renderer* renderer);

    void render(SDL_Renderer* renderer);
};

#endif //JJBA_JOTARO_H
