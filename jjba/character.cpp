//
// Created by aleca on 11/17/2018.
//

#include "character.h"

Character::Character() {}

Character::Character(Vector position, std::vector<Hitbox> mHitboxes) : SpriteObject(position, mHitboxes) {}

Character::Character(double x, double y, std::vector<Hitbox> mHitboxes) : SpriteObject(x, y, std::move(mHitboxes)) {}

void Character::update(double deltaTime) {
    Object::update(deltaTime);

    //Decrease velocity when dash-attacking
    if (mState == "ATTACK") {
        if (mVelocity.x > 0) {
            mVelocity.x = std::max(0.0, mVelocity.x - DECEL_DASH_ATTACK * deltaTime / 1000);
        } else {
            mVelocity.x = std::min(0.0, mVelocity.x + DECEL_DASH_ATTACK * deltaTime / 1000);
        }
    }

    //Check for animation end
    //Jumping animation
    if (mState == "JUMPING" && mSprites.animationDone("JUMPING", getMAnimationStartTime())) {
        setState("FALLING");
    }
    //Attack animation
    if (mState == "ATTACK" && mSprites.animationDone("ATTACK", getMAnimationStartTime())) {
        setState("IDLE");
    }
}

void Character::handleEvent(SDL_Event e) {
    //Keyboard events
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);
    if (mState == "IDLE" || mState == "WALKING") {
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case KEY_JUMP:
                    mVelocity.y = -JUMP_VELOCITY;
                    setState("JUMPING");
                case KEY_ATTACK:
                    setState("ATTACK");
                default:
                    break;
            }
        }

        //If joysticks are connected
        if (SDL_NumJoysticks() > 0) {
            if (e.type == SDL_CONTROLLERBUTTONDOWN) {
                //Motion on controller 1
                if (e.cbutton.which == 0) {
                    if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
                        mVelocity.y = -JUMP_VELOCITY;
                        setState("JUMPING");
                    } else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
                        setState("ATTACK");
                    }
                }
            }
        }
    }
}

void Character::readInput(double deltaTime, SDL_GameController *gameController) {
    if (mState == "IDLE" || mState == "WALKING") {
        double xVelocity = 0;

        //Keyboard input
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);
        //X movement
        if (currentKeyStates[SC_MOVE_LEFT] && !currentKeyStates[SC_MOVE_RIGHT]) {
            xVelocity = -getMoveSpeed();
            setMFlipType(SDL_FLIP_HORIZONTAL);
            setState("WALKING");
        } else if (!currentKeyStates[SC_MOVE_LEFT] && currentKeyStates[SC_MOVE_RIGHT]) {
            xVelocity = getMoveSpeed();
            setMFlipType(SDL_FLIP_NONE);
            setState("WALKING");
        }

        //Controller input
        if (SDL_NumJoysticks() > 0) {
            Sint16 x = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTX);
            //X movement
            if (std::abs(x) > JOYSTICK_DEAD_ZONE) {
                if (!currentKeyStates[SC_MOVE_LEFT] && !currentKeyStates[SC_MOVE_RIGHT]) {
                    xVelocity = (double)(x * getMoveSpeed()) / JOYSTICK_SCALER;
                    //Flip
                    if (x > 0) {
                        setMFlipType(SDL_FLIP_NONE);
                    } else {
                        setMFlipType(SDL_FLIP_HORIZONTAL);
                    }
                    if (mState == "IDLE") {
                        setState("WALKING");
                    }
                }
            }
        }
        if (xVelocity == 0) {
            setState("IDLE");
        }
        mVelocity.x = xVelocity;
    } else if (mState == "JUMPING" || mState == "FALLING") {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);
        //X movement
        if (currentKeyStates[SC_MOVE_LEFT] && !currentKeyStates[SC_MOVE_RIGHT]) {
            mVelocity.x = fmax(fmin(
                    mVelocity.x - getMoveSpeed() * AIR_MOVE_SPEED_MULTIPLIER * deltaTime / 1000,
                    getMoveSpeed()), -getMoveSpeed());
        } else if (!currentKeyStates[SC_MOVE_LEFT] && currentKeyStates[SC_MOVE_RIGHT]) {
            mVelocity.x = fmax(fmin(
                    mVelocity.x + getMoveSpeed() * AIR_MOVE_SPEED_MULTIPLIER * deltaTime / 1000,
                    getMoveSpeed()), -getMoveSpeed());
        }

        //If joysticks are connected
        if (SDL_NumJoysticks() > 0) {
            Sint16 x = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTX);
            //X movement
            if (std::abs(x) > JOYSTICK_DEAD_ZONE) {
                if (!currentKeyStates[SC_MOVE_LEFT] && !currentKeyStates[SC_MOVE_RIGHT]) {
                    mVelocity.x = fmax(fmin(
                            mVelocity.x + (x * getMoveSpeed() * AIR_MOVE_SPEED_MULTIPLIER * deltaTime / 1000) / JOYSTICK_SCALER,
                            getMoveSpeed()), -getMoveSpeed());
                }
            }
        }
    }

    mVelocity.y += ACCEL_GRAVITY * deltaTime / 1000;
}

void Character::render(SDL_Renderer *renderer) {
    Hitbox boundingHitbox = getBoundingHitbox(mHitboxes);
    boundingHitbox.setPosition({boundingHitbox.getX() + mPosition.x, boundingHitbox.getY() + mPosition.y});
    if(GAME_DEBUG) {
        //Draw hitbox
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect rect = boundingHitbox.getSDL_Rect();
        SDL_RenderDrawRect(renderer, &rect);
    }

    //Draw sprite
    if (getState() == "WALKING") {
        int fps = static_cast<int>(std::abs(getMVelocity().x) * WALKING_ANIMATION_SCALER);
        mSprites.render(renderer, boundingHitbox.getSDL_Rect(), getState(), getMAnimationStartTime(),
                        getMFlipType(), fps);
    } else {
        mSprites.render(renderer, boundingHitbox.getSDL_Rect(), getState(), getMAnimationStartTime(),
                        getMFlipType());
    }
}

Vector Character::staticCollisionCheck(Object other) {
    Vector response = Object::staticCollisionCheck(other);
    if (response.y >= 0 && mState != "JUMPING" && mState != "FALLING") {
        setState("FALLING");
    } else if (response.y < 0 && (mState == "JUMPING" || mState == "FALLING")) {
        setState("IDLE");
    }
    return response;
}

const std::string &Character::getState() const {
    return mState;
}

void Character::setState(const std::string &state) {
    if (Character::mState != state) {
        setMAnimationStartTime(SDL_GetTicks());
    }
    Character::mState = state;
}




