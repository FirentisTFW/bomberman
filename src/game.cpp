#include "game.h"

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Game::Game(sf::RenderWindow* _window, Player *_player) {                   // start a game
    std::cout << "Game started" << std::endl;

    std::fill(begin(gameTime), begin(gameTime)+3, 0);    // set gameTime to 0:0:0
    isGamePaused = false;
    window = _window;
    player = _player;

    loadTextures();
}

Game::~Game() {}

// ------------------------------------------ METHODS -------------------------------------------------

void Game::loadTextures() {

    // LOADING TEXTURES

    backgroundTexture.loadFromFile("images/backgrounds/background_1.png");
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);

    charactersTextures[0].loadFromFile("images/characters/character_1.png");
    charactersTextures[1].loadFromFile("images/characters/character_2.png");
    charactersTextures[2].loadFromFile("images/characters/character_3.png");
    charactersTextures[3].loadFromFile("images/characters/character_4.png");

    for (int i = 1; i < 6; i++)
        boxesTextures[i - 1].loadFromFile("images/boxes/box_" + std::to_string(i) + ".png");

    for (int i = 1; i < 5; i++)
        boxesTextures[i + 4].loadFromFile("images/boxes/stone_wall_" + std::to_string(i) + ".png");

    bombTexture.loadFromFile("images/weapons_effects/bomb.png");
    explosionTexture.loadFromFile("images/weapons_effects/explosion.png");

    specialWeaponsTextures[0].loadFromFile("images/weapons_effects/fire.png");
    specialWeaponsTextures[1].loadFromFile("images/weapons_effects/ice.png");

    bonusesTextures[0].loadFromFile("images/bonuses/b_fire.png");
    bonusesTextures[1].loadFromFile("images/bonuses/b_ice.png");
    bonusesTextures[2].loadFromFile("images/bonuses/b_range.png");
    bonusesTextures[3].loadFromFile("images/bonuses/b_bomb.png");
    bonusesTextures[4].loadFromFile("images/bonuses/b_shield.png");
    bonusesTextures[5].loadFromFile("images/bonuses/b_live.png");
    bonusesTextures[6].loadFromFile("images/bonuses/b_push.png");
    bonusesTextures[7].loadFromFile("images/bonuses/b_speed.png");
    bonusesTextures[8].loadFromFile("images/bonuses/b_digged_bomb.png");

    // ~ LOADING TEXTURES
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

void Game::updateCharacterMovementFramerate() {            
    for(Character* character : characters) {
        character->howManyFramesAfterMove++;
        character->animationTimer++;
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
        if(characters[i]->frozenTime > 0) {                                      // slow unfreezing    
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

                char colorOfExplosion = findExplosionOrFire(characters[i]->posX, characters[i]->posY);       // find which explosion (or fire) killed the character
                
                if(characters[i]->color != colorOfExplosion)                                            // you won't get points for killing yourself
                    addScoreToCharacter(colorOfExplosion, 1000);

                if (characters[i]->isHuman) {                                               // character is controlled by a player (living person)
                    player->lives--;
                    // gameOver();
                    std::cout << "Game Over 1!" << std::endl;
                }
                else {                                                                      // character is controlled by AI
                    characters.erase(characters.begin() + i);
                    i--;
                    if(characters.size() == 1) {                                            // player is the only one character left -> next level
                        std::cout << "Next level!" << std::endl;
                    }
                }
            }
        }
        else if (gameBoard[characters[i]->posY][characters[i]->posX] == "bonus") {          // character stepped on bonus - character gets a bonus and bonus is removed from the map
            int bonusesSize = bonuses.size();
            for (int j = 0; j < bonusesSize; j++) {
                if(characters[i]->posY == bonuses[j]->posY && characters[i]->posX == bonuses[j]->posX) {
                    characters[i]->steppedOnBonus(bonuses[j]->type, player->lives);
                    addScoreToCharacter(characters[i]->color, 10);
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
                
                char colorOfExplosion = findExplosionOrFire(boxes[i]->posX, boxes[i]->posY);                // find which explosion (or fire) destroyed the box
                addScoreToCharacter(colorOfExplosion, 50);

                char possibleBonus = Bonus::shouldBonusBeCreated();                     // calculate the chance for a bonus to appear here
                if(possibleBonus != '0') {                                              // create a bonus in place of destroyed box 
                    bonuses.push_back(new Bonus(boxes[i]->posX, boxes[i]->posY, possibleBonus));
                    int textureId = bonuses[bonuses.size()-1]->getTextureId();
                    bonuses[bonuses.size()-1]->setTexture(bonusesTextures[textureId]);
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

void Game::updateAnimationsOnBoard() {
    for (Bonus* bonus : bonuses) {
        int direction;
        if(bonus->animationDirectionUp) direction = -1;
        else direction = 1;

        bonus->animationCounter++;  
        if (bonus->animationCounter % 3 == 0)                                                           // move bonus slightly every 3 frames
            bonus->sprite.setPosition(bonus->sprite.getPosition().x, bonus->sprite.getPosition().y + direction);
        if (bonus->animationCounter >= 50) {
            bonus->animationCounter = 0;
            if (bonus->animationDirectionUp) bonus->animationDirectionUp = false;
            else bonus->animationDirectionUp = true;
        }
    }

    for (Bomb* bomb : bombs) {
        int direction;
        if(bomb->animationDirectionUp) direction = -1;
        else direction = 1;

        bomb->animationCounter++;
            bomb->sprite.setPosition(bomb->sprite.getPosition().x, bomb->sprite.getPosition().y + direction);
        if (bomb->animationCounter >= 10) {
            bomb->animationCounter = 0;
            if (bomb->animationDirectionUp) bomb->animationDirectionUp = false;
            else bomb->animationDirectionUp = true;
        }
    }

    for (SpecialWeapon* weapon : specialWeapons) {
        if (weapon->type == 'f') {

            if(weapon->animationCounter % 6 == 0)                                                           // change animation frame every 6 game frames
                weapon->sprite.setTextureRect(sf::IntRect(weapon->animationCounter/6*50, 0, 50, 50));
            weapon->animationCounter++;
            if (weapon->animationCounter >= 36) {
                weapon->animationCounter = 0;
            }
        }
    }

    for (Explosion* explosion : explosions) {

        if(explosion->animationCounter % 6 == 0)                                                           // change animation frame every 6 game frames
            explosion->sprite.setTextureRect(sf::IntRect(explosion->animationCounter/6*50, 0, 50, 50));
        explosion->animationCounter++;
        if (explosion->animationCounter >= 36) {
            explosion->animationCounter = 0;
        }
    }
}

char Game::findExplosionOrFire(const int objectPosX, const int objectPosY) {
    
    for(Explosion* explosion : explosions) {                                   // find the right explosion
        if (explosion->posX == objectPosX && explosion->posY == objectPosY) {
            for(Character* character : characters) {                           //find the character who planted this bomb and increase its score
                if(explosion->color == character->color) {
                    return explosion->color;
                }
            }
        }
    }                                                       

    for(SpecialWeapon* fire : specialWeapons) {                                // find the right fire (if it was fire)
        if (fire->posX == objectPosX && fire->posY == objectPosY) {
            for(Character* character : characters) {                           //find the character who started this fire and increase its score
                if(fire->color == character->color) {
                    return fire->color;
                }
            }
        }
    }

    return '0';                                                                // function shouldn't have been called
}

void Game::addScoreToCharacter(const char color, const int scoreToAdd) {

    for(Character* character : characters) {                           //find the character who started this fire and increase its score
        if(color == character->color) {
            character->score += scoreToAdd;
            if(character->isHuman)
                player->score += scoreToAdd;
            break;
        }
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

    window->draw(background);

    for (Bomb *bomb : bombs)
        window->draw(bomb->sprite);
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
    for (Bonus *bonus : bonuses)
        window->draw(bonus->sprite);
    for (Character *character : characters)
        window->draw(character->sprite);
    // std::cout << "draaaaw" << std::endl;

    gameUI->updateUI(characters, player->score);
    gameUI->drawUI(window);
}