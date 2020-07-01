#pragma once
#include "character.h"
#include "box.h"
#include "bomb.h"
#include "explosion.h"
#include "bonus.h"
#include "diggedBomb.h"
#include "specialWeapon.h"

class Game {
    
public:
    sf::RenderWindow* window;                                   // passing window by reference here to avoid drawing objects in main file
    bool isGamePaused;              
    std::array<int, 3> gameTime;                                // {minutes, seconds, frames}
    std::array<std::array<std::string, 16>, 16> gameBoard;      // what kind of object is on a given field on map (i.e. 'bomb')
    Player *player;                                            // player object (lives, score)

    std::vector<Character*> characters;
    std::vector<Box*> boxes;
    std::vector<Bomb*> bombs;
    std::vector<Explosion*> explosions;
    std::vector<Bonus*> bonuses;
    std::vector<DiggedBomb*> diggedBombs;
    std::vector<SpecialWeapon*> specialWeapons;

    Game(sf::RenderWindow* _window, Player *_player);

    ~Game();

    void updateGameTime();

    void updateCharacterMovementFramerate();                       // function called every frame for character movement to work properly

    void updateGameBoard();

    void showGameBoard();

    void draw();                                                // draw objects on the screen
};  // Game