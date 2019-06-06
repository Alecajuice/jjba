//
// Created by alecajuice on 6/5/19.
//

#ifndef JJBA_ATTACK_H
#define JJBA_ATTACK_H

#include "object.h"

class Attack : public Object {
public:
    //Constructor
    Attack(Vector position, std::vector<Hitbox> mHitboxes);

    //Member functions
};


#endif //JJBA_ATTACK_H
