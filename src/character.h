#pragma once 
#include "object.h"
#include "bomb.h"
#include "player.h"
#include "diggedBomb.h"

class Character: public Object {

    // ------------------------------------------ PROPERTIES -------------------------------------------------
public:
    bool isHuman;               // is character controlled by human or is it AI
    int howManyFramesAfterMove; // how many frames passed after last move -> needed for movement system based on speed
    char lastDirection;

    char color;
    bool shield;
    int lostShieldTimeSpan;                // after character loses shield, he can't be hit for another three seconds (he won't be killed by the bomb that crashed his shield)
    // bool bombPushing;                   // can character push planted bomb
    int speed;
    int range;
    int bombLimit;                         // how many bombs can character place at the same time (before some of them explode)
    char specialWeapon;                  // does character has any special weapon (f - fire, i - ice, d - digged bombs) | 0 means character has no special weapon
    int specialWeaponCounter;           // how many times can character use special weapons

    static std::array<float, 5> movementSpeedFramerate; // how many frames need to pass before you move a character (based on character's speed)

    // ------------------------------------------ METHODS -------------------------------------------------

    Character(bool isHuman, int _posX, int _posY, char _color);
    ~Character();

    void shouldCharacterMove(char direction, const std::array<std::array<std::string, 16>, 16> &gameBoard); // check if enough frames passed without move so character can be finally moved on the map
    
    bool isMovePossible(char direction, const std::array<std::array<std::string, 16>, 16> &gameBoard);   // collision check
    
    void move(char direction);

    void placeBomb(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<DiggedBomb *> &diggedBombs);

    void useSpecialWeapon(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<DiggedBomb *> &diggedBombs);

    void steppedOnBonus(char type, int &playersLives);                  // player gets a bonus
};