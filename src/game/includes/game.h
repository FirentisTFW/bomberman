#pragma once
#include "character.h"
#include "box.h"
#include "bomb.h"
#include "explosion.h"
#include "bonus.h"
#include "diggedBomb.h"
#include "specialWeapon.h"
#include "specialWeaponIcon.h"
#include "gameUI.h"
#include "aiBombPlacer.h"
#include "gameTextures.h"

class Game {
    private:
        void loadTextures(); 

        void resetGameBoard();

        void updateExplosionsOnBoard();

        void updateBonusesOnBoard();

        void updateSpecialWeaponsOnBoard();

        void updateDiggedBombsOnBoard();

        void updateCharactersOnBoard();

        bool shouldCharacterDieBecauseOfExplosionOrFire(const int characterIndex);

        void characterSteppedOnBonus(const int characterIndex);

        bool shouldCharacterDieBecauseOfDiggedBomb(const int characterIndex);

        void killCharacter(const int characterIndex);

        void gameOver();

        void updateBoxesOnBoard();

        void updateBombsOnBoard();

        void updateIconsOnBoard();

        void destroyBoxAndCreateBonusIfNeeded(const int boxIndex);

        char findColorOfExplosionOrFire(const int objectPosX, const int objectPosY); // when object (box, character) meets explosion or fire -> function search for this explosion or fire

        void addScoreToCharacter(const char color, const int scoreToAdd); // when object (boc, character) is destroyed -> function finds out who destryoed it and icreases its score

        void createBonus(const int posX, const int posY);                   // create a bonus in place of destroyed box

        void updateBonusesAnimations();

        void updateBombsAnimations();

        void updateSpecialWeaponsAnimations();

        void updateExplosionsWeaponsAnimations();

    public: 
        sf::RenderWindow *window; // passing window by pointer here to avoid drawing objects in main file
        GameUI *gameUI;
        GameTextures *gameTextures;

        bool isGamePaused;
        std::array<int, 3> gameTime;                           // {minutes, seconds, frames}
        std::array<std::array<std::string, 16>, 16> gameBoard; // what kind of object is on a given field on map (i.e. 'bomb')
        Player *player;                                        // player object (lives, score)

        std::vector<Character *> characters;
        std::vector<Box *> boxes;
        std::vector<Bomb *> bombs;
        std::vector<Explosion *> explosions;
        std::vector<Bonus *> bonuses;
        std::vector<DiggedBomb *> diggedBombs;
        std::vector<SpecialWeapon *> specialWeapons;
        std::vector<Icon *> specialWeaponsIcons;

        sf::Sprite background;

        Game(sf::RenderWindow *_window, Player* &_player, GameTextures *&_gameTextures, GameUI* &_gameUI);

        ~Game();

        void loadBackground();

        void updateGameTime();

        void updateCharacterMovementFramerate(); // function called every frame for character movement to work properly

        void updateGameBoard();

        void updateAnimations(); // bonuses animations

        void placeAiBombs();

        void pauseOrUnpauseGame();

        void showGameBoard();

        void draw(); // draw objects on the screen

};  // Game

