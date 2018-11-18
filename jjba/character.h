//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_CHARACTER_H
#define JJBA_CHARACTER_H

#include "object.h"

class Character : public Object {
public:
    //Constructor
    Character();
    Character(Hitbox &mHitbox);
};

#endif //JJBA_CHARACTER_H
