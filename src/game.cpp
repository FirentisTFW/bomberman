#include "game.h"

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Game::Game(sf::RenderWindow* _window, Player *_player) {                   // start a game
    std::cout << "Game started" << std::endl;

    std::fill(begin(gameTime), begin(gameTime)+3, 0);    // set gameTime to 0:0:0
    isGamePaused = false;
    window = _window;
    player = _player;

    // LOADING TEXTURES

    for(int i = 1; i < 6; i++) {
        boxesTextures[i-1].loadFromFile("images/box_" + std::to_string(i) + ".png");
    }
    for(int i = 1; i < 5; i++) {
        boxesTextures[i+4].loadFromFile("images/stone_wall_" + std::to_string(i) + ".png");
    }

    bombTexture.loadFromFile("images/bomb.png");
    explosionTexture.loadFromFile("images/explosion.png");

    specialWeaponsTextures[0].loadFromFile("images/fire.png");
    specialWeaponsTextures[1].loadFromFile("images/ice.png");

    // ~ LOADING TEXTURES

    // characters.push_back(new Character(true, 0, 0, 'g'));
    // characters.push_back(new Character(false, 8, 8, 'r'));
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

    for (Explosion* explosion : explosions){           // put the explosions on the map
        gameBoard[explosion->posY][explosion->posX] = "explosion";
    }
    for (Bonus* bonus : bonuses){                      // put the bonuses on the map
        gameBoard[bonus->posY][bonus->posX] = "bonus";
    }

    int specialWeaponsSize = specialWeapons.size();
    for (int i = 0; i < specialWeaponsSize; i++) {
        specialWeapons[i]->timeToDisappear--;
        if (specialWeapons[i]->timeToDisappear == 0) {
            specialWeapons.erase(specialWeapons.begin()+i);
            i--;
            specialWeaponsSize--;
        }
        else {
            if(specialWeapons[i]->type == 'f')
                gameBoard[specialWeapons[i]->posY][specialWeapons[i]->posX] = "fire";
            else {
                if(gameBoard[specialWeapons[i]->posY][specialWeapons[i]->posX] != "explosion")              
                    gameBoard[specialWeapons[i]->posY][specialWeapons[i]->posX] = "ice";
                else {                                                                                  // explosion makes ice melt
                    specialWeapons.erase(specialWeapons.begin() + i);
                    i--;
                    specialWeaponsSize--;
                }
            }

        }
    }

    int diggedBombsSize = diggedBombs.size();
    for (int i = 0; i < diggedBombsSize; i++){                      // put the digged bombs on the map
        if(gameBoard[diggedBombs[i]->posY][diggedBombs[i]->posX] == "explosion" || gameBoard[diggedBombs[i]->posY][diggedBombs[i]->posX] == "fire") {              // digged bomb exploded
            diggedBombs.erase(diggedBombs.begin() + i);
            i--;
            diggedBombsSize--;
        }
        else
            gameBoard[diggedBombs[i]->posY][diggedBombs[i]->posX] = "digged_bomb";
    }

    // CHARACTERS LOOP
    for (int i = 0; i < characters.size(); i++) {
        if (characters[i]->lostShieldTimeSpan > 0)                               // character just lost its shield, can't be hurt again 
                characters[i]->lostShieldTimeSpan--;
        if(characters[i]->frozenTime > 0) {                                      // slowly unfreezing    
            characters[i]->frozenTime--;
            if (characters[i]->frozenTime <= 0)
                characters[i]->frozen = false;
        }
        
        if (gameBoard[characters[i]->posY][characters[i]->posX] == "explosion" || gameBoard[characters[i]->posY][characters[i]->posX] == "fire") {      // character is on the field where explosion happened
            if (characters[i]->shield) {
                characters[i]->shield = false;
                characters[i]->lostShieldTimeSpan = 180;                                    // after losing shield, character can't be hit for 3 seconds

                gameBoard[characters[i]->posY][characters[i]->posX] = "character";
            }
            else if(characters[i]->lostShieldTimeSpan <= 0) {                              // character doesn't have "after-hit protection"
                if (characters[i]->isHuman) {                                             // character is controlled by a player (living person)
                    player->lives--;
                    // gameOver();
                    std::cout << "Game Over 1!" << std::endl;
                }
                else {                                                                      // character is controlled by AI
                    characters.erase(characters.begin() + i);
                    i--;
                }
            }
        }
        else if (gameBoard[characters[i]->posY][characters[i]->posX] == "bonus") {          // character stepped on bonus - character gets a bonus and bonus is removed from the map
            int bonusesSize = bonuses.size();
            for (int j = 0; j < bonusesSize; j++) {
                if(characters[i]->posY == bonuses[j]->posY && characters[i]->posX == bonuses[j]->posX) {
                    characters[i]->steppedOnBonus(bonuses[j]->type, player->lives);
                    std::cout << "y: " << characters[i]->posY << std::endl;
                    std::cout << "x: " << characters[i]->posX << std::endl;
                    bonuses.erase(bonuses.begin() + j);     
                    break;
                }
            }
            gameBoard[characters[i]->posY][characters[i]->posX] = "character";
        }
        else if (gameBoard[characters[i]->posY][characters[i]->posX] == "digged_bomb") {    // character stepped on a digged bomb
            int diggedBombsSize = diggedBombs.size();
            for (int j = 0; j < diggedBombsSize; j++) {                                     // search for a right bomb          
                if (characters[i]->posX == diggedBombs[j]->posX && characters[i]->posY == diggedBombs[j]->posY) {    // the right bomb has been found
                    if(diggedBombs[j]->color != characters[i]->color) {         // the bomb has been planted by another character (you can't lose life on your own bomb)
                        if (characters[i]->shield) {
                            characters[i]->shield = false;
                            gameBoard[characters[i]->posY][characters[i]->posX] = "character";
                        }
                        else {
                            if (characters[i]->isHuman) {                       // character is controlled by a player (living person)
                                player->lives--;
                                // gameOver();
                                std::cout << "Game Over 1!" << std::endl;
                            }
                            else {                                              // character is controlled by AI
                                characters.erase(characters.begin() + i);
                                i--;
                            }
                        }
                            diggedBombs.erase(diggedBombs.begin() + j);
                        break;
                    }
                }
            }
        }
        else if (gameBoard[characters[i]->posY][characters[i]->posX] == "ice") {            // character is on the filed with ice - freeze the character
            characters[i]->frozen = true;
            characters[i]->frozenTime = 300;
        }
        else                                                                                // character is on empty field
            gameBoard[characters[i]->posY][characters[i]->posX] = "character";
    }   // CHARACTERS LOOP

    int boxesSize = boxes.size();
    for (int i=0; i< boxesSize; i++) {
        if (gameBoard[boxes[i]->posY][boxes[i]->posX] == "explosion" || gameBoard[boxes[i]->posY][boxes[i]->posX] == "fire") {
            if(boxes[i]->isDestroyable) {
                char possibleBonus = Bonus::shouldBonusBeCreated();                     // calculate the chance fr a bonus to appear here
                if(possibleBonus != '0') {                                              // create a bonus in place of destroyed box 
                    bonuses.push_back(new Bonus(boxes[i]->posX, boxes[i]->posY, possibleBonus));
                    gameBoard[boxes[i]->posY][boxes[i]->posX] = "bonus";
                }
                boxes.erase(boxes.begin() + i);
                i--;
            }
            else 
                gameBoard[boxes[i]->posY][boxes[i]->posX] = "wall";
        }
        else {
            if(boxes[i]->isDestroyable)
                gameBoard[boxes[i]->posY][boxes[i]->posX] = "box";
            else
                gameBoard[boxes[i]->posY][boxes[i]->posX] = "wall";

        }
    }

    int bombsSize = bombs.size();
    for (int i = 0; i < bombsSize; i++) {
        if (gameBoard[bombs[i]->posY][bombs[i]->posX] == "explosion" || gameBoard[bombs[i]->posY][bombs[i]->posX] == "fire") {
            bombs[i]->explode(explosions, gameBoard, explosionTexture);
            bombs.erase(bombs.begin() + i);
            bombsSize = bombs.size();
            i--;
        }
        else if(gameBoard[bombs[i]->posY][bombs[i]->posX] == "ice") {
            *bombs[i]->charactersBombLimit += 1;
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
        window->draw(bomb->sprite);
    for (Bonus *bonus : bonuses)
        window->draw(bonus->rect);
    for (Explosion *explosion : explosions)
        window->draw(explosion->sprite);
    for (SpecialWeapon *specialWeapon : specialWeapons)
        window->draw(specialWeapon->sprite);
    for (Box *box : boxes) {
        if(gameBoard[box->posY][box->posX] == "explosion") {
            if(!box->isDestroyable)
                window->draw(box->sprite);
        }
        else
            window->draw(box->sprite);
    }
    for (Character *character : characters)
        window->draw(character->rect);
    // std::cout << "draaaaw" << std::endl;
}