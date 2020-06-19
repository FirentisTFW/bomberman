#pragma once
#include "object.h"
#include "explosion.h"

class Bomb : public Object {
    public:
        int range;                          // how many fields in each directions will be affected by explosion
        int timeToExplode;                  // how many frames before the bomb explodes
        char color;

        Bomb(int _posX, int _posY, int _range, char _color);
        ~Bomb();

        void explode(std::vector<Explosion *> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard); // create an explosion in four directions
        bool collisionCheckForExplosion();
        // function below can be optimalised (for example check every 10-20 frames, not every frame)
        static void checkBombsTimers(std::vector<Bomb *> &bombs, std::vector<Explosion *> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard); // check every bomb and see if it should explode
};