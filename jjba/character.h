//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_CHARACTER_H
#define JJBA_CHARACTER_H

#include "object.h"
#include "constants.h"

class Character : public SpriteObject {
private:
    std::string mState = "IDLE";

public:
    //Constructor
    Character();

    explicit Character(Hitbox &mHitbox);

    //Member functions
    virtual void handleEvent(SDL_Event e);

    virtual void readInput(SDL_GameController* gameController);

    virtual void render(SDL_Renderer* renderer);
    virtual const int getMoveSpeed() const = 0;

    //Getters and setters
    const std::string &getState() const;
    void setState(const std::string &state);
};

#endif //JJBA_CHARACTER_H
