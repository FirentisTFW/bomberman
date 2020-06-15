#pragma once
#include "player.h"

class Game {
    
public:
    sf::RenderWindow* window;                                   // passing window by reference here to avoid drawing objects in main file
    bool isGamePaused;              
    std::array<int, 3> gameTime;                                // {minutes, seconds, frames}

    std::vector<Player*> players;
    // std::vector<Wall*> walls;
    // std::vector<Box*> boxes;

    Game(sf::RenderWindow* _window);

    ~Game();

    void updateGameTime();

    void updatePlayerMovementFramerate();

    void draw();
};  // Game