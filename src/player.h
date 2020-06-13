#pragma once 
#include "object.h"

class Player: public Object {
    public:
        bool isHuman;                       // is player controlled by human or is it AI
        int lives;

        // bool shield;
        // bool bombPushing;                   // can player push planted bomb
        int speed;
        // int range;
        //int bombLimit;                         // how many bombs can player place at the same time (before some of them explode)
        // int specialWeapon;                  // does player has any special weapon (fire, ice etc.) | 0 means players has no special weapon
        // int specialWeaponCounter;           // how many times can player use special weapons

        Player(bool isHuman);
        ~Player();

        void move(char direction);
};