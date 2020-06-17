#pragma once
#include "object.h"

class Explosion : public Object {

    public:
        int timeToLive;

        Explosion(int _posX, int _posY, char color);
        ~Explosion();

        static void checkForInactiveExplosions(std::vector<Explosion*> &explosions);
};