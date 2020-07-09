#pragma once
#include "object.h"

class SpecialWeapon : public Object {
    public:
        char type;      // f - fire, i - ice
        int timeToDisappear;            // how many frames till the effects of the weapon disappear
        char color;                     // needed to increase the score - color identifies the character who used this weapon

        SpecialWeapon(int _posX, int _posY, char _type, char _color);
        ~SpecialWeapon();

};