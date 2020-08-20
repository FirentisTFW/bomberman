#pragma once
#include "object.h"
#include "explosion.h"

class Bomb : public Object {
    private:
        void makeExplosionsInDirection(const char direction, std::vector<Explosion *> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard, sf::Texture &explosionTexture);

        int getXMultiplierForExplosion(const char direction);

        int getYMultiplierForExplosion(const char direction);

    public:
        int range;                          // how many fields in each directions will be affected by explosion
        int timeToExplode;                  // how many frames before the bomb explodes
        char color;
        int movingBombTimer;                // to control speed while bomb is rolling after somebody pushed it (how many frames has to past before the bomb will be moved) | -1 means bomb wasn't pushed by anybody
        int direction;                      // for moving bombs

        int animationCounter;
        bool animationDirectionUp;          // animation - is bomb currently moving up or down

        int *charactersBombLimit;

        Bomb(int _posX, int _posY, int _range, char _color, int *_charactersBombLimit);
        ~Bomb();

        void explode(std::vector<Explosion *> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard, sf::Texture &explosionTexture); // create an explosion in four directions

        bool moveBomb(char _direction, std::array<std::array<std::string, 16>, 16> &gameBoard);                     // 

        bool collisionCheckForExplosion();

        static void checkBombsTimers(std::vector<Bomb *> &bombs, std::vector<Explosion *> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard, sf::Texture &explosionTexture); // check every bomb and see if it should explode
};