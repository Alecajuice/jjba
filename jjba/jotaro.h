//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_JOTARO_H
#define JJBA_JOTARO_H

#include "standUser.h"

class Jotaro : public StandUser {
public:
    //Constructor
    Jotaro();

    //Member functions
    void loadMedia(SDL_Renderer* renderer) override;
    void render(SDL_Renderer* renderer) override;

    const int getMoveSpeed() const override;
    const int getStandMoveSpeed() const override;
    const int getStandRange() const override;
};

#endif //JJBA_JOTARO_H
