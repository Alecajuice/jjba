//
// Created by aleca on 11/17/2018.
//

#include "character.h"

Character::Character() {}

Character::Character(Vector position, std::vector<Hitbox> mHitboxes) : SpriteObject(position, mHitboxes) {}

Character::Character(double x, double y, std::vector<Hitbox> mHitboxes) : SpriteObject(x, y, mHitboxes) {}

void Character::handleEvent(SDL_Event e) {
    //Keyboard events
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_a:
                setMVelocity({static_cast<double>(-getMoveSpeed()), 0});
                setMFlipType(SDL_FLIP_HORIZONTAL);
                setState("WALKING");
                break;
            case SDLK_d:
                setMVelocity({static_cast<double>(getMoveSpeed()), 0});
                setMFlipType(SDL_FLIP_NONE);
                setState("WALKING");
                break;
            default:
                break;
        }
    } else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_a:
                if(currentKeyStates[SDL_SCANCODE_D]) {
                    setMVelocity({static_cast<double>(getMoveSpeed()), 0});
                    setMFlipType(SDL_FLIP_NONE);
                } else {
                    setMVelocity({0, 0});
                    setState("IDLE");
                }
                break;
            case SDLK_d:
                if(currentKeyStates[SDL_SCANCODE_A]) {
                    setMVelocity({static_cast<double>(-getMoveSpeed()), 0});
                    setMFlipType(SDL_FLIP_HORIZONTAL);
                } else {
                    setMVelocity({0, 0});
                    setState("IDLE");
                }
                break;
            default:
                break;
        }
    }

    //If joysticks are connected
    if (SDL_NumJoysticks() > 1) {
        //Joystick events
        if (e.type == SDL_CONTROLLERAXISMOTION) {
            //Motion on controller 0
            if (e.caxis.which == 1) {
                //X axis motion
                if (e.jaxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                    //If keyboard movement keys are not pressed
                    if(!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D]) {
                        //Outside of dead zone
                        if (std::abs(e.caxis.value) > JOYSTICK_DEAD_ZONE) {
                            double x = static_cast<double>(e.caxis.value * getMoveSpeed()) / JOYSTICK_SCALER;
                            setMVelocity({x, 0});
                            if(x > 0) {
                                setMFlipType(SDL_FLIP_NONE);
                            } else {
                                setMFlipType(SDL_FLIP_HORIZONTAL);
                            }
                            setState("WALKING");
                        } else {
                            setMVelocity({0, 0});
                            setState("IDLE");
                        }
                    }
                } //Y axis motion
                else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {

                }
            }
        }
    }


}

void Character::readInput(SDL_GameController* gameController) {

}

void Character::render(SDL_Renderer *renderer) {
    //Draw hitbox
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    Hitbox boundingHitbox = getBoundingHitbox(mHitboxes);
    boundingHitbox.setPosition({boundingHitbox.getX() + mPosition.x, boundingHitbox.getY() + mPosition.y});
    auto* tempHitbox = new SDL_Rect;
    *tempHitbox = boundingHitbox.getSDL_Rect();
    SDL_RenderDrawRect(renderer, tempHitbox);
    delete tempHitbox;

    //Draw sprite
    if(getState() == "WALKING") {
        int fps = static_cast<int>(std::abs(getMVelocity().x) * WALKING_ANIMATION_SCALER);
        mSprites.render(renderer, boundingHitbox.getSDL_Rect(), getState(), getMAnimationStartTime(), getMFlipType(), fps);
    } else {
        mSprites.render(renderer, boundingHitbox.getSDL_Rect(), getState(), getMAnimationStartTime(), getMFlipType());
    }
}

const std::string &Character::getState() const {
    return mState;
}

void Character::setState(const std::string &state) {
    if(Character::mState != state) {
        setMAnimationStartTime(SDL_GetTicks());
    }
    Character::mState = state;
}


