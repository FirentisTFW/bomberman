#include "game.h"

Game::Game(sf::RenderWindow* _window) {                   // start a game
    std::cout << "Game started" << std::endl;

    std::fill(begin(gameTime), begin(gameTime)+3, 0);    // set gameTime to 0:0:0
    isGamePaused = false;
    window = _window;

    players.push_back(new Player(true, 0, 0, 'g'));
    players.push_back(new Player(false, 8, 8, 'r'));
    boxes.push_back(new Box(true, 5, 5));
    boxes.push_back(new Box(true, 5, 8));
    boxes.push_back(new Box(true, 10, 12));
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
    for (Explosion* explosion : explosions){
        gameBoard[explosion->posY][explosion->posX] = "explosion";
    }
    for (int i = 0; i < players.size(); i++){
        if (gameBoard[players[i]->posY][players[i]->posX] == "explosion") {             // player is on the fied where explosion happened
            if(players[i]->shield) {
                players[i]->shield = false;

                // ADD TIME SPAN BEFORE PLAYER CAN BE HIT AGAIN (LIKE 1-2 SECONDS)

                gameBoard[players[i]->posY][players[i]->posX] = "player";
            }
            else if (players[i]->isHuman) {                                             // character is controlled by a player (living person)
                players[i]->lives--;
                // gameOver();
                std::cout << "Game Over 1!" << std::endl;
            }
            else {                                                                      // player is controlled by AI
                players.erase(players.begin() + i);
                i--;
            }
        }
        else
            gameBoard[players[i]->posY][players[i]->posX] = "player";
    }

    int boxesSize = boxes.size();
    for (int i=0; i< boxesSize; i++){
        if (gameBoard[boxes[i]->posY][boxes[i]->posX] == "explosion") {
            if(boxes[i]->isDestroyable) {
                boxes.erase(boxes.begin() + i);
                i--;
            }
            else 
                gameBoard[boxes[i]->posY][boxes[i]->posX] = "box";
        }
        else
            gameBoard[boxes[i]->posY][boxes[i]->posX] = "box";
    }
    int bombsSize = bombs.size();
    for (int i = 0; i < bombsSize; i++) {
        if (gameBoard[bombs[i]->posY][bombs[i]->posX] == "explosion") {
            bombs[i]->explode(explosions, gameBoard);
            bombs.erase(bombs.begin() + i);
            bombsSize = bombs.size();
            i--;
        }
        else
            gameBoard[bombs[i]->posY][bombs[i]->posX] = "bomb";
    }

}

void Game::showGameBoard() {

    for(int i=0; i<16; i++) {                           // print an array
        for (int j = 0; j < 16; j++) {
            std::cout << gameBoard[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void Game::draw() {
    for (Bomb *bomb : bombs)
        window->draw(bomb->rect);
    for (Explosion *explosion : explosions)
        window->draw(explosion->rect);
    for (Box *box : boxes)
        window->draw(box->rect);
    for (Player *player : players)
        window->draw(player->rect);
    // std::cout << "draaaaw" << std::endl;
}