#pragma once 
#include "object.h"

class Player: public Object {

    // ------------------------------------------ PROPERTIES -------------------------------------------------

public:
    bool isHuman;               // is player controlled by human or is it AI
    int howManyFramesAfterMove; // how many frames passed after last move -> needed for movement system based on speed
    char lastDirection;

    int lives;
    // bool shield;
    // bool bombPushing;                   // can player push planted bomb
    int speed;
    // int range;
    // int bombLimit;                      // how many bombs can player place at the same time (before some of them explode)
    // int specialWeapon;                  // does player has any special weapon (fire, ice etc.) | 0 means players has no special weapon
    // int specialWeaponCounter;           // how many times can player use special weapons

    static std::array<float, 5> movementSpeedFramerate; // how many frames need to pass before you move a player (based on player's speed)

    // ------------------------------------------ METHODS -------------------------------------------------

    Player(bool isHuman, int _posX, int _posY);
    ~Player();

    void shouldPlayerMove(char direction); // check if enough frames passed without move so player can be finally moved on the map
    void move(char direction);
};