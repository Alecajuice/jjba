//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_GAME_H
#define JJBA_GAME_H

#include "jotaro.h"
#include "level.h"

class Game {
private:
    Jotaro player;
    Level level;
public:
    //Constructor
    Game(SDL_Renderer* renderer);

    //Update
    bool update(const double deltaTime, SDL_GameController* gameController);

    //Render
    void render(SDL_Renderer* renderer);

    //Collision checks
    void collisionChecks();
};

#endif //JJBA_GAME_H
