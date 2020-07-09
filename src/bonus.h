#pragma once
#include "object.h"

class Bonus : public Object {
    

    public:
        char type;     // s - speed, l - live, h - shield, r - range, b - bomb
        int animationCounter;               
        int animationDirectionUp;           // animation - is bonus currently moving up or down

        Bonus(int _posX, int _posY, char _type);
        ~Bonus();

        static char shouldBonusBeCreated();                 // calculate a chance for a bonus to appear, returns char indicating bonus type

        int getTextureId();
};