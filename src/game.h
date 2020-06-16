#pragma once
#include "player.h"
#include "box.h"

class Game {
    
public:
    sf::RenderWindow* window;                                   // passing window by reference here to avoid drawing objects in main file
    bool isGamePaused;              
    std::array<int, 3> gameTime;                                // {minutes, seconds, frames}
    std::array<std::array<std::string, 16>, 16> gameBoard;      // what kind of object is on a given field on map (i.e. 'bomb')

    std::vector<Player*> players;
    std::vector<Box*> boxes;

    Game(sf::RenderWindow* _window);

    ~Game();

    void updateGameTime();

    void updatePlayerMovementFramerate();                       // function called every frame for player movement to work properly

    void updateGameBoard();

    void draw();                                                // draw objects on the screen
};  // Game