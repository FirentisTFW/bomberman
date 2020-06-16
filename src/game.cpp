#include "game.h"

Game::Game(sf::RenderWindow* _window) {                   // start a game
    std::cout << "Game started" << std::endl;

    std::fill(begin(gameTime), begin(gameTime)+3, 0);    // set gameTime to 0:0:0
    isGamePaused = false;
    window = _window;

    players.push_back(new Player(true, 0, 0));
    boxes.push_back(new Box(false, 5, 5));
    boxes.push_back(new Box(false, 5, 8));
    boxes.push_back(new Box(false, 10, 12));
    boxes.push_back(new Box(false, 2, 12));
    // std::fill(begin(gameBoard), begin(gameBoard) + 16, 0); // set gameTime to 0:0:0
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

void Game::updatePlayerMovementFramerate() {            
    for(Player* player : players) {
        player->howManyFramesAfterMove++;
    }
}

void Game::updateGameBoard() {
    for (int i = 0; i < 16; i++) {                      // fill everything with empty strings assuming there's nothing there
        for (int j = 0; j < 16; j++) {
            gameBoard[i][j] = "0";
        }
    }
    for (Player* player : players){
        gameBoard[player->posY][player->posX] = "player";
    }
    for (Box* box : boxes){
        gameBoard[box->posY][box->posX] = "box";
    }

    for(int i=0; i<16; i++) {                           // print an array
        for (int j = 0; j < 16; j++) {
            std::cout << gameBoard[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

void Game::draw() {
    for (Player *player : players)
        window->draw(player->rect);
    for (Box *box : boxes)
        window->draw(box->rect);
    // std::cout << "draaaaw" << std::endl;
}