#pragma once 
#include "object.h"
#include "bomb.h"
#include "player.h"

class Character: public Object {

    // ------------------------------------------ PROPERTIES -------------------------------------------------
public:
    bool isHuman;               // is character controlled by human or is it AI
    int howManyFramesAfterMove; // how many frames passed after last move -> needed for movement system based on speed
    char lastDirection;

    char color;
    bool shield;
    // bool bombPushing;                   // can character push planted bomb
    int speed;
    int range;
    int bombLimit;                      // how many bombs can character place at the same time (before some of them explode)
    // int specialWeapon;                  // does character has any special weapon (fire, ice etc.) | 0 means characters has no special weapon
    // int specialWeaponCounter;           // how many times can character use special weapons

    static std::array<float, 5> movementSpeedFramerate; // how many frames need to pass before you move a character (based on character's speed)

    // ------------------------------------------ METHODS -------------------------------------------------

    Character(bool isHuman, int _posX, int _posY, char _color);
    ~Character();

    void shouldCharacterMove(char direction, const std::array<std::array<std::string, 16>, 16> &gameBoard); // check if enough frames passed without move so character can be finally moved on the map
    
    bool isMovePossible(char direction, const std::array<std::array<std::string, 16>, 16> &gameBoard);   // collision check
    
    void move(char direction);
    
    void placeBomb(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard);
};