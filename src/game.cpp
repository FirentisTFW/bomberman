#include "game.h"

Game::Game(sf::RenderWindow* _window) {                   // start a game
    std::cout << "Game started" << std::endl;

    std::fill(begin(gameTime), begin(gameTime)+3, 0);    // set gameTime to 0:0:0
    isGamePaused = false;
    window = _window;

    players.push_back(new Player(true, 0, 0));
}

void Game::updateGameTime() {
    
    gameTime[2]++;                                      // time update - start from frames
    if (gameTime[2] >= 60) {                            // update seconds if needed
        gameTime[2] = 0;
        gameTime[1]++;
        if (gameTime[1] >= 60) {                        // update minutes if needed
            gameTime[1] = 0;
            gameTime[0]++;
        }
    }
}

void Game::updatePlayerMovementFramerate() {            // function called every frame for player movement to work properly
    for(Player* player : players) {
        player->howManyFramesAfterMove++;
    }
}

void Game::draw() {                                      // draw objects on the screen
    for (Player* player : players) 
        window->draw(player->rect); 
    // std::cout << "draaaaw" << std::endl;
}