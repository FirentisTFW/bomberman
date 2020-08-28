#pragma once 
#include "object.h"
#include "bomb.h"
#include "player.h"
#include "diggedBomb.h"
#include "box.h"
#include "specialWeapon.h"
#include "specialWeaponIcon.h"
#include "aiBombChecker.h"

class Character: public Object {
    private:
        void updateAnimationDirection();

        void updateAnimationIfNeeded();

        void setAnimationDirection();

        bool shouldCharacterMove(char direction); // check if enough frames passed without move so character can be finally moved on the map

        bool didCharacterPushBomb(const int posX, const int posY, std::vector<Bomb *> &bombs, char direction, std::array<std::array<std::string, 16>, 16> &gameBoard);

        void digBomb(std::vector<DiggedBomb *> &diggedBombs, std::array<std::array<std::string, 16>, 16> &gameBoard);

        void tryToUseFire(const int xSummand, const int ySummand, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &texture, std::array<std::array<std::string, 16>, 16> &gameBoard);

        void useFire(const int PosX, const int posY, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &texture, std::array<std::array<std::string, 16>, 16> &gameBoard);

        void tryToUseIce(const int xSummand, const int ySummand, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &texture, std::array<std::array<std::string, 16>, 16> &gameBoard);

        void useIce(const int PosX, const int posY, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &texture, std::array<std::array<std::string, 16>, 16> &gameBoard);

        // ------------------------------------------ PROPERTIES -------------------------------------------------
    public:
        bool isHuman;               // is character controlled by human or is it AI
        int howManyFramesAfterMove; // how many frames passed after last move -> needed for movement system based on speed
        char lastDirection;
        char lastTriedDirection;
        int animationDirection; // 0 - down, 1 - right, 2 - left, 3 - up
        int animationTimer;     // change animation frame after every 10 frames in game
        int animationCounter;   // which frame in animation is currently being displayed

        char color;
        bool shield;
        int lostShieldTimeSpan; // after character loses shield, he can't be hit for another three seconds (he won't be killed by the bomb that crashed his shield)
        bool bombPushing;       // can character push planted bomb
        bool frozen;            // is character frozen by an ice weapon (character can't move)
        int frozenTime;         // how many frames longer character will be frozen

        int score;
        int speed;
        int range;
        int bombLimit;            // how many bombs can character place at the same time (before some of them explode)
        char specialWeapon;       // does character has any special weapon (f - fire, i - ice, d - digged bombs) | 0 means character has no special weapon
        int specialWeaponCounter; // how many times can character use special weapons

        static std::array<float, 5> movementSpeedFramerate;   // how many frames need to pass before you move a character (based on character's speed)
        static std::array<float, 5> aiMovementSpeedFramerate; // how many frames need to pass before you move a character (based on character's speed)

        // ------------------------------------------ METHODS -------------------------------------------------

        Character(bool isHuman, int _posX, int _posY, char _color);
        ~Character();

        void tryToMove(char direction, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs);

        bool isMovePossible(const int posX, const int posY, char direction, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs); // collision check

        int getDangerOfMove(const int posX, const int posY, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs);

        int getDangerOfCurrentPosition(std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs);

        void move(char direction);

        bool didCharacterMove(const int expectedXPos, const int expectedYPos);

        int getSuggestedXPosition(const char direction);

        int getSuggestedYPosition(const char direction);

        void tryToPlaceBomb(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<DiggedBomb *> &diggedBombs, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &bombTexture, std::array<sf::Texture, 2> &specialWeaponsTextures);

        void useSpecialWeapon(std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<DiggedBomb *> &diggedBombs, std::vector<SpecialWeapon *> &specialWeapons, std::array<sf::Texture, 2> &specialWeaponsTextures);

        void steppedOnBonus(const char type, int &playersLives, std::vector<Icon *> &specialWeaponsIcons, std::array<sf::Texture, 3> &iconsTextures, sf::Font &font); // player gets a bonus

        void continueUnfreezing();

        bool doesHaveAfterHitProtection();
};