#include "game.h"

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Game::Game(sf::RenderWindow* _window, Player* &_player, GameTextures* &_gameTextures, GameUI* &_gameUI) {                   // start a game
    std::cout << "Game started" << std::endl;

    std::fill(begin(gameTime), begin(gameTime)+3, 0);    // set gameTime to 0:0:0
    isGamePaused = false;
    window = _window;
    player = _player;
    gameTextures = _gameTextures;
    gameUI = _gameUI;

    gameTextures->loadTextures();
}

Game::~Game() {}

// ------------------------------------------ METHODS -------------------------------------------------

void Game::loadBackground() {
    background.setTexture(gameTextures->backgroundTexture);
    background.setPosition(0, 0);
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

    resetGameBoard();

    updateBonusesOnBoard();

    updateExplosionsOnBoard();

    updateSpecialWeaponsOnBoard();

    updateDiggedBombsOnBoard();

    updateCharactersOnBoard();

    updateBoxesOnBoard();

    updateBombsOnBoard();

    updateIconsOnBoard();
}

void Game::resetGameBoard() {
    for (int i = 0; i < 16; i++) {                      // fill everything with zeros assuming there's nothing there
        for (int j = 0; j < 16; j++) {
            gameBoard[i][j] = "0";
        }
    }
}

void Game::updateExplosionsOnBoard() {
    for (Explosion* explosion : explosions){           // put the explosions on the map
        gameBoard[explosion->posY][explosion->posX] = "explosion";
    }

}

void Game::updateBonusesOnBoard() {
    for (Bonus* bonus : bonuses){                      // put the bonuses on the map
        gameBoard[bonus->posY][bonus->posX] = "bonus";
    }
}

void Game::updateSpecialWeaponsOnBoard() {
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
}

void Game::updateDiggedBombsOnBoard() {
    int diggedBombsSize = diggedBombs.size();
    for (int i = 0; i < diggedBombsSize; i++) {
        if (gameBoard[diggedBombs[i]->posY][diggedBombs[i]->posX] == "explosion" || gameBoard[diggedBombs[i]->posY][diggedBombs[i]->posX] == "fire") { // digged bomb exploded
            diggedBombs.erase(diggedBombs.begin() + i);
            i--;
            diggedBombsSize--;
        }
        else
            gameBoard[diggedBombs[i]->posY][diggedBombs[i]->posX] = "digged_bomb";
    }
}

void Game::updateCharactersOnBoard() {
    for (int i = 0; i < characters.size(); i++) {
        if (characters[i]->lostShieldTimeSpan > 0)                               // character just lost its shield, can't be hurt again 
                characters[i]->lostShieldTimeSpan--;
        if(characters[i]->frozen)                                          
            characters[i]->continueUnfreezing();
        
        if (gameBoard[characters[i]->posY][characters[i]->posX] == "explosion" || gameBoard[characters[i]->posY][characters[i]->posX] == "fire") {     // character is on the field where explosion happened
            if (shouldCharacterDieBecauseOfExplosionOrFire(i)) {
                if(!characters[i]->isHuman) {
                    killCharacter(i);
                    i--;
                }
                else
                    gameOver();
            }
        }
        else if (gameBoard[characters[i]->posY][characters[i]->posX] == "bonus")          // character stepped on bonus - character gets a bonus and bonus is removed from the map
            characterSteppedOnBonus(i);
        else if (gameBoard[characters[i]->posY][characters[i]->posX] == "digged_bomb") {    // character stepped on a digged bomb
            if(shouldCharacterDieBecauseOfDiggedBomb(i)) {
                if (!characters[i]->isHuman) {
                    killCharacter(i);
                    i--;
                }
                else
                    gameOver();
            }
        }
        else if (gameBoard[characters[i]->posY][characters[i]->posX] == "ice") {            // character is on the filed with ice - freeze the character
            characters[i]->frozen = true;
            characters[i]->frozenTime = 300;
        }
        else                                                                                // character is on empty field
            gameBoard[characters[i]->posY][characters[i]->posX] = "character";
    }
}

bool Game::shouldCharacterDieBecauseOfExplosionOrFire(const int characterIndex) {
    if (characters[characterIndex]->shield) {
        characters[characterIndex]->shield = false;
        characters[characterIndex]->lostShieldTimeSpan = 180;                                    // after losing shield, character can't be hit for 3 seconds
        gameBoard[characters[characterIndex]->posY][characters[characterIndex]->posX] = "character";
        return false;
    }
    else if (!characters[characterIndex]->doesHaveAfterHitProtection()){                              // character doesn't have "after-hit protection"
        char colorOfExplosion = findColorOfExplosionOrFire(characters[characterIndex]->posX, characters[characterIndex]->posY);       // find which explosion (or fire) killed the character
        if(characters[characterIndex]->color != colorOfExplosion)                                            // you won't get points for killing yourself
            addScoreToCharacter(colorOfExplosion, 1000);

        return true;
    }
    return true;
}

void Game::characterSteppedOnBonus(const int characterIndex) {
    int bonusesSize = bonuses.size();
    for (int j = 0; j < bonusesSize; j++) {
        if(characters[characterIndex]->posY == bonuses[j]->posY && characters[characterIndex]->posX == bonuses[j]->posX) {
            characters[characterIndex]->steppedOnBonus(bonuses[j]->type, player->lives, specialWeaponsIcons, gameTextures->iconsTextures, gameUI->font);
            addScoreToCharacter(characters[characterIndex]->color, 10);
            bonuses.erase(bonuses.begin() + j);     
            break;
        }
    }
    gameBoard[characters[characterIndex]->posY][characters[characterIndex]->posX] = "character";
}

bool Game::shouldCharacterDieBecauseOfDiggedBomb(const int characterIndex) {
    int diggedBombsSize = diggedBombs.size();
    for (int j = 0; j < diggedBombsSize; j++) {                                     // search for a right bomb          
        if (characters[characterIndex]->posX == diggedBombs[j]->posX && characters[characterIndex]->posY == diggedBombs[j]->posY) {    // the right bomb has been found
            if(diggedBombs[j]->color != characters[characterIndex]->color) {         // the bomb has been planted by another character (you can't lose life on your own bomb)
                explosions.push_back(
                    new Explosion(characters[characterIndex]->posX, characters[characterIndex]->posY, 
                    characters[characterIndex]->color, gameTextures->explosionTexture));
                diggedBombs.erase(diggedBombs.begin() + j);
                if (characters[characterIndex]->shield) {
                    characters[characterIndex]->shield = false;
                    characters[characterIndex]->lostShieldTimeSpan = 180; // after losing shield, character can't be hit for 3 seconds
                    gameBoard[characters[characterIndex]->posY][characters[characterIndex]->posX] = "character";
                    return false;
                }
                else
                    return true;
            }
            return false;
        }
    }
}

void Game::killCharacter(const int characterIndex) {
    characters.erase(characters.begin() + characterIndex);
    if(characters.size() == 1)                                            // player is the only one character left -> next level
        std::cout << "Next level!" << std::endl;

}

void Game::gameOver() {
    // TODO
    std::cout << "Game over!" << std::endl;
}

void Game::updateBoxesOnBoard() {
    int boxesSize = boxes.size();
    for (int i=0; i< boxesSize; i++) {
        if (gameBoard[boxes[i]->posY][boxes[i]->posX] == "explosion" || gameBoard[boxes[i]->posY][boxes[i]->posX] == "fire") {
            if(boxes[i]->isDestroyable) {
                destroyBoxAndCreateBonusIfNeeded(i);
                boxesSize = boxes.size();
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
}

void Game::updateBombsOnBoard() {
    int bombsSize = bombs.size();
    for (int i = 0; i < bombsSize; i++) {
        if (gameBoard[bombs[i]->posY][bombs[i]->posX] == "explosion" || gameBoard[bombs[i]->posY][bombs[i]->posX] == "fire") {
            bombs[i]->explode(explosions, gameBoard, gameTextures->explosionTexture);
            bombs.erase(bombs.begin() + i);
            bombsSize = bombs.size();
            i--;
        }
        else if(gameBoard[bombs[i]->posY][bombs[i]->posX] == "ice") {           // freeze a bomb
            *bombs[i]->charactersBombLimit += 1;
            bombs.erase(bombs.begin() + i);
            bombsSize = bombs.size();
            i--;
        }
        else
            gameBoard[bombs[i]->posY][bombs[i]->posX] = "bomb";
    }
}

void Game::updateIconsOnBoard() {
    int iconsSize = specialWeaponsIcons.size();
    for (int i = 0; i < iconsSize; i++) {
        bool isOwnerStillAlive = false;
        for(Character* character : characters) {
            if(character->color == specialWeaponsIcons[i]->color) {                 // icon belongs to this character
                isOwnerStillAlive = true;
                if(character->specialWeaponCounter == 0) {
                    specialWeaponsIcons.erase(specialWeaponsIcons.begin()+i);
                    i--;
                    iconsSize--;
                    break;
                }
                specialWeaponsIcons[i]->updatePosition(character->posX, character->posY, character->specialWeaponCounter);
                break;
            }
        }
        if(!isOwnerStillAlive) {
            specialWeaponsIcons.erase(specialWeaponsIcons.begin() + i);
            i--;
            iconsSize--;
        }
    }   
}

void Game::destroyBoxAndCreateBonusIfNeeded(const int boxIndex) {
    char color = findColorOfExplosionOrFire(boxes[boxIndex]->posX, boxes[boxIndex]->posY); // find which explosion (or fire) destroyed the box
    addScoreToCharacter(color, 50);

    if (Bonus::shouldBonusBeCreated())
        createBonus(boxes[boxIndex]->posX, boxes[boxIndex]->posY);

    boxes.erase(boxes.begin() + boxIndex);
}

char Game::findColorOfExplosionOrFire(const int objectPosX, const int objectPosY) {
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

void Game::createBonus(const int posX, const int posY) {
    char bonusType = Bonus::whichBonusShouldBeCreated();

    bonuses.push_back(new Bonus(posX, posY, bonusType));
    int textureId = bonuses[bonuses.size() - 1]->getTextureId();
    bonuses[bonuses.size() - 1]->setTexture(gameTextures->bonusesTextures[textureId]);
    // gameBoard[posY][posX] = "bonus";
}

void Game::updateAnimations() {

    updateBonusesAnimations();

    updateBombsAnimations();

    updateSpecialWeaponsAnimations();

    updateExplosionsWeaponsAnimations();
}

void Game::updateBonusesAnimations() {
    for (Bonus* bonus : bonuses) {
        int direction;
        if(bonus->animationDirectionUp) direction = -1;
        else direction = 1;

        bonus->animationCounter++;  
        if (bonus->animationCounter % 3 == 0)                                                           // move bonus slightly every 3 frames
            bonus->sprite.setPosition(bonus->sprite.getPosition().x, bonus->sprite.getPosition().y + direction);
        if (bonus->animationCounter >= 50) {                                                        // change direction
            bonus->animationCounter = 0;
            bonus->animationDirectionUp = !bonus->animationDirectionUp;
        }
    }
}

void Game::updateBombsAnimations() {
    for (Bomb* bomb : bombs) {
        int direction;
        if(bomb->animationDirectionUp) direction = -1;
        else direction = 1;

        bomb->animationCounter++;
            bomb->sprite.setPosition(bomb->sprite.getPosition().x, bomb->sprite.getPosition().y + direction);
        if (bomb->animationCounter >= 10) {
            bomb->animationCounter = 0;
            bomb->animationDirectionUp = !bomb->animationDirectionUp;
        }
    }

}

void Game::updateSpecialWeaponsAnimations() {
    for (SpecialWeapon* weapon : specialWeapons) {
        if (weapon->type == 'f') {
            if(weapon->animationCounter % 6 == 0)                                                           // change animation frame every 6 game frames
                weapon->sprite.setTextureRect(sf::IntRect(weapon->animationCounter/6*50, 0, 50, 50));
            weapon->animationCounter++;
            if (weapon->animationCounter >= 36)                                                 // went through full animation cycle - start from beginning
                weapon->animationCounter = 0;
        }
    }
}

void Game::updateExplosionsWeaponsAnimations() {
    for (Explosion* explosion : explosions) {
        if(explosion->animationCounter % 6 == 0)                                                           // change animation frame every 6 game frames
            explosion->sprite.setTextureRect(sf::IntRect(explosion->animationCounter/6*50, 0, 50, 50));
        explosion->animationCounter++;
        if (explosion->animationCounter >= 36) {
            explosion->animationCounter = 0;
        }
    }
}

void Game::placeAiBombs() {
    for(int i = 1; i < characters.size(); i++) {
        AiBombPlacer bombPlacer = AiBombPlacer(characters[i], gameBoard, bombs);
        if(bombPlacer.isItWorthToPlaceBombHere())
            characters[i]->tryToPlaceBomb(bombs, gameBoard, diggedBombs, specialWeapons, gameTextures->bombTexture, gameTextures->specialWeaponsTextures);
    }
}

void Game::pauseOrUnpauseGame() {
    isGamePaused = !isGamePaused;
    std::cout << "Game paused/unpaused" << std::endl;
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
    for (Icon *icon : specialWeaponsIcons) {
        window->draw(icon->sprite);
        window->draw(icon->counter);
    }

    gameUI->updateUI(characters, player->score);
    gameUI->drawUI(window);
}