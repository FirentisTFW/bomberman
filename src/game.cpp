#include "game.h"

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Game::Game(sf::RenderWindow* _window) {                   // start a game
    std::cout << "Game started" << std::endl;

    std::fill(begin(gameTime), begin(gameTime)+3, 0);    // set gameTime to 0:0:0
    isGamePaused = false;
    window = _window;

    characters.push_back(new Character(true, 0, 0, 'g'));
    characters.push_back(new Character(false, 8, 8, 'r'));
    boxes.push_back(new Box(true, 5, 5));
    boxes.push_back(new Box(true, 5, 8));
    boxes.push_back(new Box(true, 10, 12));
    boxes.push_back(new Box(false, 2, 12));
    // std::fill(begin(gameBoard), begin(gameBoard) + 16, 0); // set gameTime to 0:0:0
}

Game::~Game() {}

// ------------------------------------------ METHODS -------------------------------------------------

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

void Game::updateCharacterMovementFramerate() {            
    for(Character* character : characters) {
        character->howManyFramesAfterMove++;
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
    for (int i = 0; i < characters.size(); i++){
        if (gameBoard[characters[i]->posY][characters[i]->posX] == "explosion") {             // character is on the fied where explosion happened
            if(characters[i]->shield) {
                characters[i]->shield = false;

                // ADD TIME SPAN BEFORE PLAYER CAN BE HIT AGAIN (LIKE 1-2 SECONDS)

                gameBoard[characters[i]->posY][characters[i]->posX] = "character";
            }
            else if (characters[i]->isHuman) {                                             // character is controlled by a character (living person)
                characters[i]->lives--;
                // gameOver();
                std::cout << "Game Over 1!" << std::endl;
            }
            else {                                                                      // character is controlled by AI
                characters.erase(characters.begin() + i);
                i--;
            }
        }
        else
            gameBoard[characters[i]->posY][characters[i]->posX] = "character";
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
    for (Character *character : characters)
        window->draw(character->rect);
    // std::cout << "draaaaw" << std::endl;
}