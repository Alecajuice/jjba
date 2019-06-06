//
// Created by aleca on 11/25/2018.
//

#ifndef JJBA_CONSTANTS_H
#define JJBA_CONSTANTS_H

//Debug state
const bool GAME_DEBUG = true;

//Joystick constants
const int JOYSTICK_DEAD_ZONE = 17000;
const int JOYSTICK_SCALER = 32768;

//Animation constants
const double WALKING_ANIMATION_SCALER = 0.1;

//Movement constants
const double ACCEL_GRAVITY = 3000;
const double JUMP_VELOCITY = 1200;
const double AIR_MOVE_SPEED_MULTIPLIER = 10;
const double DECEL_DASH_ATTACK = 750;

//Character constants
const int JOTARO_MOVE_SPEED = 300;
const int JOTARO_STAND_MOVE_SPEED = 600;
const int JOTARO_STAND_RANGE = 300;

//Controls
//Keyboard
const SDL_Keycode KEY_JUMP = SDLK_SPACE;
const SDL_Keycode KEY_ATTACK = SDLK_LSHIFT;

const Uint8 SC_MOVE_LEFT = SDL_SCANCODE_A;
const Uint8 SC_MOVE_RIGHT = SDL_SCANCODE_D;
const Uint8 SC_MOVESTAND_LEFT = SDL_SCANCODE_J;
const Uint8 SC_MOVESTAND_RIGHT = SDL_SCANCODE_L;
const Uint8 SC_MOVESTAND_UP = SDL_SCANCODE_I;
const Uint8 SC_MOVESTAND_DOWN = SDL_SCANCODE_K;

#endif //JJBA_CONSTANTS_H
