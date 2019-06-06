#include <utility>

#include <utility>

#include <utility>

//
// Created by aleca on 11/17/2018.
//

#include "standUser.h"

StandUser::StandUser() = default;

StandUser::StandUser(Vector position, Vector standPosition, std::vector<Hitbox> mHitboxes,
                     std::vector<Hitbox> mStandHitboxes) : Character(position, std::move(mHitboxes)) {
    mStand.setMPosition(standPosition);
    mStand.setMHitboxes(std::move(mStandHitboxes));
}

StandUser::StandUser(double x, double y, double standX, double standY, std::vector<Hitbox> mHitboxes,
                     std::vector<Hitbox> mStandHitboxes) : StandUser({x, y}, {standX, standY}, std::move(mHitboxes),
                                                                     std::move(mStandHitboxes)) {}

void StandUser::render(SDL_Renderer *renderer) {
    //Draw stand
    Hitbox boundingHitbox = getBoundingHitbox(mStand.getMHitboxes());
    boundingHitbox.setPosition({boundingHitbox.getX() + mStand.getMPosition().x,
                                boundingHitbox.getY() + mStand.getMPosition().y});
    if(GAME_DEBUG) {
        //Draw hitbox
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_Rect rect = boundingHitbox.getSDL_Rect();
        SDL_RenderDrawRect(renderer, &rect);
    }

    //Draw sprite
    mSprites.render(renderer, boundingHitbox.getSDL_Rect(), mStandState, mStandAnimationStartTime, mStandFlipType);

    //Draw character
    Character::render(renderer);
}

void StandUser::handleEvent(SDL_Event e) {
    Character::handleEvent(e);

    //Keyboard events
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_SPACE:
                setStandState("STAND_ATTACK");
                break;
            default:
                break;
        }
    }
    //If joysticks are connected
    if (SDL_NumJoysticks() > 1) {
        //Button events
        if (e.type == SDL_CONTROLLERBUTTONDOWN) {
            //Motion on controller 1
            if (e.cbutton.which == 1) {
                if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
                    setStandState("STAND_ATTACK");
                }
            }
        }
    }

}

void StandUser::readInput(SDL_GameController *gameController) {
    Character::readInput(gameController);

    double xVelocity = mVelocity.x;
    double yVelocity = mVelocity.y;

    //Keyboard input
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);
    //X movement
    if (currentKeyStates[SDL_SCANCODE_J] && !currentKeyStates[SDL_SCANCODE_L]) {
        xVelocity = -(double) getStandMoveSpeed();
        if (mStandState == "STAND_IDLE")
            mStandFlipType = SDL_FLIP_HORIZONTAL;
    } else if (!currentKeyStates[SDL_SCANCODE_J] && currentKeyStates[SDL_SCANCODE_L]) {
        xVelocity = (double) getStandMoveSpeed();
        if (mStandState == "STAND_IDLE")
            mStandFlipType = SDL_FLIP_NONE;
    }
    //Y movement
    if (currentKeyStates[SDL_SCANCODE_I] && !currentKeyStates[SDL_SCANCODE_K]) {
        yVelocity = -(double) getStandMoveSpeed();
    } else if (!currentKeyStates[SDL_SCANCODE_I] && currentKeyStates[SDL_SCANCODE_K]) {
        yVelocity = (double) getStandMoveSpeed();
    }

    //Controller input
    if (SDL_NumJoysticks() > 1) {
        Sint16 x = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_RIGHTX);
        Sint16 y = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_RIGHTY);
        //X movement
        if (std::abs(x) > JOYSTICK_DEAD_ZONE) {
            if (!currentKeyStates[SDL_SCANCODE_J] && !currentKeyStates[SDL_SCANCODE_L]) {
                xVelocity += (double) (x * (getStandMoveSpeed() - (x / std::abs(x)) * mVelocity.x)) / JOYSTICK_SCALER;
                //Flip stand
                if (mStandState == "STAND_IDLE") {
                    if (x > 0) {
                        mStandFlipType = SDL_FLIP_NONE;
                    } else {
                        mStandFlipType = SDL_FLIP_HORIZONTAL;
                    }
                }
            }
        }
        //Y movement
        if (std::abs(y) > JOYSTICK_DEAD_ZONE) {
            if (!currentKeyStates[SDL_SCANCODE_I] && !currentKeyStates[SDL_SCANCODE_K]) {
                yVelocity += (double) (y * (getStandMoveSpeed() - (y / std::abs(y)) * mVelocity.y)) / JOYSTICK_SCALER;
            }
        }
    }

    mStand.setMVelocity({xVelocity, yVelocity});
}

const std::string &StandUser::getStandState() const {
    return mStandState;
}

void StandUser::setStandState(const std::string &state) {
    if (StandUser::mStandState != state) {
        mStandAnimationStartTime = SDL_GetTicks();
    }
    StandUser::mStandState = state;
}

void StandUser::update(double deltaTime) {
    Character::update(deltaTime);
    //Check for animation end
    //Attack animation
    if (mStandState == "STAND_ATTACK" && mSprites.animationDone("STAND_ATTACK", mStandAnimationStartTime)) {
        setStandState("STAND_IDLE");
    }
    mStand.update(deltaTime);


}

Vector StandUser::staticCollisionCheck(Object other) {
    Vector response = Character::staticCollisionCheck(other);
    mStand.staticCollisionCheck(other);
    //Keep stand within range
    double dx = mStand.getMPosition().x - getMPosition().x;
    double dy = mStand.getMPosition().y - getMPosition().y;
    double dist = std::pow(std::pow(dx, 2) + std::pow(dy, 2), 0.5);
    //If outside of range
    if (dist > getStandRange()) {
        mStand.setPosition(getMPosition().x + dx * getStandRange() / dist,
                           getMPosition().y + dy * getStandRange() / dist);
    }
    return response;
}


