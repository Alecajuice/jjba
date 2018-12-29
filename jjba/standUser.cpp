//
// Created by aleca on 11/17/2018.
//

#include "standUser.h"

StandUser::StandUser() {

}

StandUser::StandUser(Hitbox mHitbox, Hitbox mStandHitbox) : Character(mHitbox) {
    mStand.setMHitbox(mStandHitbox);
}

void StandUser::render(SDL_Renderer *renderer) {
    //Draw stand
    //Draw hitbox
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    auto *tempStandHitbox = new SDL_Rect;
    *tempStandHitbox = mStand.getMHitbox().getSDL_Rect();
    SDL_RenderDrawRect(renderer, tempStandHitbox);
    delete tempStandHitbox;

    //Draw sprite
    mSprites.render(renderer, mStand.getMHitbox().getSDL_Rect(), mStandState, mStandAnimationStartTime, mStandFlipType);

    //Draw character
    Character::render(renderer);
}

void StandUser::handleEvent(SDL_Event e) {
    Character::handleEvent(e);

    //Keyboard events
//    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_SPACE:
                setStandState("STAND_ATTACK");
                break;
//            case SDLK_j:
//                mStand.setMVelocity({static_cast<double>(-getStandMoveSpeed()), mStand.getMVelocity().y});
//                mStandFlipType = SDL_FLIP_HORIZONTAL;
////                setStandState("WALKING");
//                break;
//            case SDLK_l:
//                mStand.setMVelocity({static_cast<double>(getStandMoveSpeed()), mStand.getMVelocity().y});
//                mStandFlipType = SDL_FLIP_NONE;
////                setStandState("WALKING");
//                break;
//            case SDLK_i:
//                mStand.setMVelocity({mStand.getMVelocity().x, static_cast<double>(-getStandMoveSpeed())});
////                setStandState("WALKING");
//                break;
//            case SDLK_k:
//                mStand.setMVelocity({mStand.getMVelocity().x, static_cast<double>(getStandMoveSpeed())});
////                setStandState("WALKING");
//                break;
//            default:
//                break;
        }
//    } else if (e.type == SDL_KEYUP) {
//        switch (e.key.keysym.sym) {
//            case SDLK_j:
//                if(currentKeyStates[SDL_SCANCODE_L]) {
//                    mStand.setMVelocity({static_cast<double>(getStandMoveSpeed()), mStand.getMVelocity().y});
//                    mStandFlipType = SDL_FLIP_NONE;
//                } else {
//                    mStand.setMVelocity({0, mStand.getMVelocity().y});
////                    setState("IDLE");
//                }
//                break;
//            case SDLK_l:
//                if(currentKeyStates[SDL_SCANCODE_J]) {
//                    mStand.setMVelocity({static_cast<double>(-getStandMoveSpeed()), mStand.getMVelocity().y});
//                    mStandFlipType = SDL_FLIP_HORIZONTAL;
//                } else {
//                    mStand.setMVelocity({0, mStand.getMVelocity().y});
////                    setState("IDLE");
//                }
//                break;
//            case SDLK_i:
//                if(currentKeyStates[SDL_SCANCODE_K]) {
//                    mStand.setMVelocity({mStand.getMVelocity().x, static_cast<double>(getStandMoveSpeed())});
////                    mStandFlipType = SDL_FLIP_NONE;
//                } else {
//                    mStand.setMVelocity({mStand.getMVelocity().x, 0});
////                    setState("IDLE");
//                }
//                break;
//            case SDLK_k:
//                if(currentKeyStates[SDL_SCANCODE_I]) {
//                    mStand.setMVelocity({mStand.getMVelocity().x, static_cast<double>(-getStandMoveSpeed())});
////                    mStandFlipType = SDL_FLIP_HORIZONTAL;
//                } else {
//                    mStand.setMVelocity({mStand.getMVelocity().x, 0});
////                    setState("IDLE");
//                }
//                break;
//            default:
//                break;
//        }
    }
//
//    //If joysticks are connected
    if (SDL_NumJoysticks() > 1) {
        //Joystick events
        if (e.type == SDL_CONTROLLERBUTTONDOWN) {
            //Motion on controller 1
            if (e.caxis.which == 1) {
                if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
                    setStandState("STAND_ATTACK");
                }
            }
        }
    }
//        if (e.type == SDL_CONTROLLERAXISMOTION) {
//            //Motion on controller 1
//            if (e.caxis.which == 1) {
//                //X axis motion
//                if (e.jaxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
//                    //If keyboard movement keys are not pressed
//                    if(!currentKeyStates[SDL_SCANCODE_J] && !currentKeyStates[SDL_SCANCODE_L]) {
//                        //Outside of dead zone
//                        if (std::abs(e.caxis.value) > JOYSTICK_DEAD_ZONE) {
//                            double x = static_cast<double>(e.caxis.value * getStandMoveSpeed()) / JOYSTICK_SCALER;
//                            mStand.setMVelocity({x, mStand.getMVelocity().y});
//                            if(x > 0) {
//                                mStandFlipType = SDL_FLIP_NONE;
//                            } else {
//                                mStandFlipType = SDL_FLIP_HORIZONTAL;
//                            }
////                            setState("WALKING");
//                        } else {
//                            mStand.setMVelocity({0, mStand.getMVelocity().y});
////                            setState("IDLE");
//                        }
//                    }
//
//                } //Y axis motion
//                else if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
//                    //If keyboard movement keys are not pressed
//                    if(!currentKeyStates[SDL_SCANCODE_I] && !currentKeyStates[SDL_SCANCODE_K]) {
//                        //Outside of dead zone
//                        if (std::abs(e.caxis.value) > JOYSTICK_DEAD_ZONE) {
//                            double y = static_cast<double>(e.caxis.value * getStandMoveSpeed()) / JOYSTICK_SCALER;
//                            mStand.setMVelocity({mStand.getMVelocity().x, y});
////                            setState("WALKING");
//                        } else {
//                            mStand.setMVelocity({mStand.getMVelocity().x, 0});
////                            setState("IDLE");
//                        }
//                    }
//                }
//            }
//        }
//    }
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
        //Y movement
        if (std::abs(y) > JOYSTICK_DEAD_ZONE) {
            yVelocity += (double) (y * (getStandMoveSpeed() - (y / std::abs(y)) * mVelocity.y)) / JOYSTICK_SCALER;
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
    Object::update(deltaTime);
    //Check for animation end
    //Attack animation
    if (mStandState == "STAND_ATTACK" && mSprites.animationDone("STAND_ATTACK", mStandAnimationStartTime)) {
        setStandState("STAND_IDLE");
    }
    mStand.update(deltaTime);
}

