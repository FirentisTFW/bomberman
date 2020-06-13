#include "game.h"

Game::Game(sf::RenderWindow* _window) {                   // start a game
    std::cout << "Game started" << std::endl;

    isGamePaused = false;
    window = _window;

    players.push_back(new Player(true));
}

void Game::draw() {                                      // draw objects on the screen
    for (Player* player : players) 
        window->draw(player->rect); 
    // std::cout << "draaaaw" << std::endl;
}