#pragma once
#include "object.h"

class Explosion : public Object {

    public:
        int timeToLive;
        char color;                     // needed to increase the score - color identifies the character who caused explosion

        Explosion(int _posX, int _posY, char _color);
        ~Explosion();

        static void checkForInactiveExplosions(std::vector<Explosion*> &explosions);
};