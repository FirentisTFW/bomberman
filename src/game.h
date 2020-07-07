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

    sf::Texture backgroundTexture;
    sf::Sprite background;

    std::array<sf::Texture, 4> charactersTextures;
    std::array<sf::Texture, 10> boxesTextures;
    std::array<sf::Texture, 2> specialWeaponsTextures;          // 0 fire, 1 - ice
    std::array<sf::Texture, 9> bonusesTextures;
    sf::Texture bombTexture;
    sf::Texture explosionTexture;
    
    Game(sf::RenderWindow* _window, Player *_player);

    ~Game();

    void loadTextures();

    void updateGameTime();

    void updateCharacterMovementFramerate();                       // function called every frame for character movement to work properly

    void updateGameBoard();

    void showGameBoard();

    void draw();                                                // draw objects on the screen
};  // Game

