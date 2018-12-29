//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_STANDUSER_H
#define JJBA_STANDUSER_H

#include "character.h"
#include "constants.h"

class StandUser : public Character {
private:
    Object mStand;
    std::string mStandState = "STAND_IDLE";
    bool mStandOut = true; //Change to false

    //Stand animation variables
    Uint32 mStandAnimationStartTime;
    SDL_RendererFlip mStandFlipType = SDL_FLIP_NONE;
public:
    //Constructors
    StandUser();

    explicit StandUser(Hitbox mHitbox, Hitbox mStandHitbox);

    //Member functions
    void update(double deltaTime) override;

    void render(SDL_Renderer *renderer) override;

    void handleEvent(SDL_Event e) override;

    void readInput(SDL_GameController* gameController) override;

    //Getters and setters
    virtual const int getStandMoveSpeed() const = 0;

    const std::string &getStandState() const;
    void setStandState(const std::string &state);
};

#endif //JJBA_STANDUSER_H
