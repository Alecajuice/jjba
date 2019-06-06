//
// Created by aleca on 11/25/2018.
//

#ifndef JJBA_CONSTANTS_H
#define JJBA_CONSTANTS_H

//Debug state
const bool GAME_DEBUG = false;

//Joystick constants
const int JOYSTICK_DEAD_ZONE = 8000;
const int JOYSTICK_SCALER = 32768;

//Animation constants
const double WALKING_ANIMATION_SCALER = 0.1;

//Movement constants
const double ACCEL_GRAVITY = 3000;
const double JUMP_VELOCITY = 1200;
const double AIR_MOVE_SPEED_MULTIPLIER = 0.1;

//Character constants
const int JOTARO_MOVE_SPEED = 300;
const int JOTARO_STAND_MOVE_SPEED = 600;
const int JOTARO_STAND_RANGE = 300;

#endif //JJBA_CONSTANTS_H
