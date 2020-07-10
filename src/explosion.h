#pragma once
#include "object.h"

class Explosion : public Object {

    public:
        int timeToLive;
        char color;                     // needed to increase the score - color identifies the character who caused explosion
        int animationCounter;

        Explosion(int _posX, int _posY, char _color, sf::Texture &texture);
        ~Explosion();

        static void checkForInactiveExplosions(std::vector<Explosion*> &explosions);
};