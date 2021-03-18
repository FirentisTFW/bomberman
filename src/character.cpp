#include "character.h"
#include "specialWeapon.h"

// ------------------------------------------ STATIC PROPERTIES -------------------------------------------------

std::array<float, 5> Character::movementSpeedFramerate = {5.0, 4.0, 3.0, 2.0, 1.0};
std::array<float, 5> Character::aiMovementSpeedFramerate = {12.0, 9.0, 6.0, 4.0, 3.0};

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Character::Character(bool _isHuman, int _posX, int _posY, char _color) {
    
    score = 0;

    isHuman = _isHuman;
    speed = 1;
    bombLimit = 1;
    shield = false;
    bombPushing = false;
    lostShieldTimeSpan = 0;
    frozen = false;
    frozenTime = 0;

    posX = _posX;
    posY = _posY;
    color = _color;
    howManyFramesAfterMove = 0;
    lastDirection = ' ';
    lastTriedDirection = ' ';
    animationDirection = 0;
    animationCounter = 0;
    animationTimer = 0;

    range = 1;
    specialWeapon = '0';                  
    specialWeaponCounter = 0;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::Green);

    setUiScoreIndex();
}

Character::~Character() {}

// ------------------------------------------ METHODS -------------------------------------------------

void Character::setUiScoreIndex() {
    if(color == 'b')
        uiScoreIndex = 0;
    else if(color == 'g')
        uiScoreIndex = 1;
    else if(color == 'r')
        uiScoreIndex = 2;
    else if(color == 'y')
        uiScoreIndex = 3;
}

void Character::updateAnimationDirection() {
    sprite.setTextureRect(sf::IntRect(50 * animationCounter, 50 * animationDirection, 50, 50));
}

void Character::updateAnimationIfNeeded() {
    if (animationTimer >= 3) {
        animationTimer = 0;
        animationCounter++;
        if(animationCounter >= 4)
            animationCounter = 0;
    }
}

void Character::tryToMove(char direction, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    if(shouldCharacterMove(direction)) {
        updateAnimationIfNeeded();
        const int newXPosition = getSuggestedXPosition(direction);
        const int newYPosition = getSuggestedYPosition(direction);
        if (isMovePossible(newXPosition, newYPosition, direction, gameBoard, bombs)) {
            if(isHuman)
                move(direction);
            else {
                int dangerOfMove = getDangerOfMove(newXPosition, newYPosition, gameBoard, bombs);
                if (dangerOfMove <= 0) {
                    move(direction);
                    updateAnimationDirection();
                }
            }
        }
    }

    lastTriedDirection = direction;
    setAnimationDirection();
    if(isHuman)
        updateAnimationDirection();
}

bool Character::shouldCharacterMove(char direction) {
    if (frozen)                                               // character can't move if frozen by another character
        return false;                                  
    if(lastDirection != direction && isHuman)                 // player can change directions whenever he wants because he won't do it as fast as computer
        return true;
    if(isHuman) {
        if(howManyFramesAfterMove >= Character::movementSpeedFramerate[speed-1])
            return true;
    }
    else if (howManyFramesAfterMove >= Character::aiMovementSpeedFramerate[speed - 1])
        return true;
    return false;
}

bool Character::isMovePossible(const int posX, const int posY, char direction, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    if(isPositionOnTheMap(posX, posY)) {
        if (gameBoard[posY][posX] != "box" && gameBoard[posY][posX] != "wall" && gameBoard[posY][posX] != "bomb" && gameBoard[posY][posX] != "ice") // field character wants to step on is possible to step on
            return true;
        if (gameBoard[posY][posX] == "bomb" && bombPushing == true && isHuman)                            // character wants to step on the bomb and character can push the bombs
            return didCharacterPushBomb(posX, posY, bombs, direction, gameBoard);
        return false;
    }
    return false;
}

int Character::getDangerOfMove(const int posX, const int posY, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    if(!isPositionOnTheMap(posX, posY))
        return 200;
    if (gameBoard[posY][posX] == "explosion" || gameBoard[posY][posX] == "fire")
        return 100;

    std::vector<int> bombsPositionsVertical = AiBombChecker::getPositionOfClosestBombsVertical(posX, posY, gameBoard);
    std::vector<int> bombsPositionsHorizontal = AiBombChecker::getPositionOfClosestBombsHorizontal(posX, posY, gameBoard);

    // check bombs and their ranges
    int verticalDanger = AiBombChecker::getVerticalDirectionDanger(posX, posY, bombsPositionsVertical, bombs);
    int horizontalDanger = AiBombChecker::getHorizontalDirectionDanger(posX, posY, bombsPositionsHorizontal, bombs);

    return std::max(verticalDanger, horizontalDanger);
}

int Character::getDangerOfCurrentPosition(std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs) {
    return getDangerOfMove(posX, posY, gameBoard, bombs);
}

void Character::move(char direction) {
    switch(direction) {
        case 'u':
            if(posY > 0) {        // character can move -> still on the map
                rect.move(0, -50);
                sprite.move(0, -50);
                posY--;
            }
            break;
        case 'd':
            if(posY < 15) {        
                rect.move(0, 50);
                sprite.move(0, 50);
                posY++;
            }
            break;
        case 'l':
            if(posX > 0) {        
                rect.move(-50, 0);
                sprite.move(-50, 0);
                posX--;
            }
            break;
        case 'r':
            if(posX < 15) {        
                rect.move(50, 0);
                sprite.move(50, 0);
                posX++;
            }
            break;
        default:
            break;
    }

    sprite.setTextureRect(sf::IntRect(50 * animationCounter, 50 * animationDirection, 50, 50));
    lastDirection = direction;
    howManyFramesAfterMove = 0;
}

void Character::setAnimationDirection() {
    switch (lastTriedDirection) {
        case 'u':
            animationDirection = 3;
            break;
        case 'd':
            animationDirection = 0;
            break;
        case 'l':
            animationDirection = 2;
            break;
        case 'r':
            animationDirection = 1;
            break;
        default:
            break;
    }
}

bool Character::didCharacterMove(const int expectedXPos, const int expectedYPos) {
    return posX == expectedXPos && posY == expectedYPos;
}

int Character::getSuggestedXPosition(char direction) {
    if (direction == 'l')
        return posX - 1;
    if (direction == 'r')
        return posX + 1;
    return posX;
}

int Character::getSuggestedYPosition(char direction) {
    if (direction == 'u')
        return posY - 1;
    if (direction == 'd')
        return posY + 1;
    return posY;
}

bool Character::didCharacterPushBomb(const int posX, const int posY, std::vector<Bomb *> &bombs, char direction, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    bool wasBombPushed = false;
    int bombsSize = bombs.size();
    for(int i = 0; i < bombsSize; i++) {
        if(bombs[i]->posX == posX && bombs[i]->posY == posY) {               // the right bomb has been found - try to push the bomb
            wasBombPushed = bombs[i]->moveBomb(direction, gameBoard);
            break;
        }
    }
    return wasBombPushed;
}

void Character::tryToPlaceBomb(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard,std::vector<DiggedBomb*> &diggedBombs, std::vector<SpecialWeapon*> &specialWeapons, sf::Texture &bombTexture, std::array<sf::Texture, 2> &specialWeaponsTextures) {
    if(specialWeaponCounter > 0) {                  // character has a special weapon
        useSpecialWeapon(gameBoard, diggedBombs, specialWeapons, specialWeaponsTextures);
        return;
    }

    if(bombLimit > 0) {
        if(gameBoard[posY][posX] != "bomb" && gameBoard[posY][posX] != "digged_bomb") {                                   // two bombs can't be placed on the same field
            bombLimit--;
            bombs.push_back(new Bomb(posX, posY, range, color, &bombLimit));
            bombs[bombs.size()-1]->setTexture(bombTexture);
            gameBoard[posY][posX] = "bomb";
        }
    }
}

void Character::useSpecialWeapon(std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<DiggedBomb *> &diggedBombs, std::vector<SpecialWeapon *> &specialWeapons, std::array<sf::Texture, 2> &specialWeaponsTextures) {
    if(specialWeapon == 'd') {          // DIGGED BOMB
        if(SpecialWeapon::canYouDigBombHere(posX, posY, gameBoard))
            digBomb(diggedBombs, gameBoard);
    }
    else {
        int addX = SpecialWeapon::getXSummand(lastTriedDirection);
        int addY = SpecialWeapon::getYSummand(lastTriedDirection);
        if(specialWeapon == 'f')                                                      // FIRE
            tryToUseFire(addX, addY, specialWeapons, specialWeaponsTextures[0], gameBoard);
        else                                                                       // ICE
            tryToUseIce(addX, addY, specialWeapons, specialWeaponsTextures[1], gameBoard);
    }
}

void Character::digBomb(std::vector<DiggedBomb *> &diggedBombs, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    diggedBombs.push_back(new DiggedBomb(posX, posY, color));
    gameBoard[posY][posX] = "digged_bomb";
    specialWeaponCounter--;
}

void Character::tryToUseFire(const int xSummand, const int ySummand, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &texture, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    bool wasSpecialWeaponUsed = false;      // used to determine if you should decrease the weapon counter
    for(int i = 1; i < 4; i++) {
        if (SpecialWeapon::canFireBeUsedHere(posX + xSummand * i, posY + ySummand * i, gameBoard)) {
            useFire(posX + xSummand * i, posY + ySummand * i, specialWeapons, texture, gameBoard);
            wasSpecialWeaponUsed = true;
        }
        else
            break;
    }
    if(wasSpecialWeaponUsed)
        specialWeaponCounter--;
}

void Character::useFire(const int posX, const int posY, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &texture, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    specialWeapons.push_back(new SpecialWeapon(posX, posY, 'f', color, texture));
    gameBoard[posY][posX] = "fire";
}

void Character::tryToUseIce(const int xSummand, const int ySummand, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &texture, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    bool wasSpecialWeaponUsed = false;      // used to determine if you should decrease the weapon counter
    for(int i = 1; i < 4; i++) {
        if (SpecialWeapon::canIceBeUsedHere(posX + xSummand * i, posY + ySummand * i, gameBoard)) {
            useIce(posX + xSummand * i, posY + ySummand * i, specialWeapons, texture, gameBoard);
            wasSpecialWeaponUsed = true;
        }
        else
            break;
    }
    if(wasSpecialWeaponUsed)
        specialWeaponCounter--;
}

void Character::useIce(const int posX, const int posY, std::vector<SpecialWeapon *> &specialWeapons, sf::Texture &texture, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    specialWeapons.push_back(new SpecialWeapon(posX, posY, 'i', color, texture));
    gameBoard[posY][posX] = "ice";
}

void Character::steppedOnBonus(const char type, int &playersLives, std::vector<Icon*> &specialWeaponsIcons, std::array<sf::Texture, 3> &iconsTextures, sf::Font &font) {
    switch(type) {                                                    // check bonus type                
        case 'r':
            range++;
            break;
        case 'b':
            bombLimit++;
            break;
        case 's':
            if(speed <5)                // 5 - maximal speed
                speed++;
            break;
        case 'h':
            shield = true;
            break;
        case 'l':
            if (isHuman)
                playersLives++;
            break;  
        case 'p':
            bombPushing = true;
            break;  

            // SPECIAL WEAPONS
        case 'f':
            specialWeapon = 'f';     
            specialWeaponCounter = 2;
            specialWeaponsIcons.push_back(new Icon(posX, posY, color, iconsTextures[0], font));
            break;
        case 'd':
            specialWeapon = 'd';     
            specialWeaponCounter = 2;
            specialWeaponsIcons.push_back(new Icon(posX, posY, color, iconsTextures[2], font));
            break;
        case 'i':
            specialWeapon = 'i';     
            specialWeaponCounter = 1;
            specialWeaponsIcons.push_back(new Icon(posX, posY, color, iconsTextures[1], font));
            break;
        default:
            break;
    }
}

void Character::continueUnfreezing() {
    frozenTime--;
    if (frozenTime <= 0)
        frozen = false;
}

bool Character::doesHaveAfterHitProtection() {
    return lostShieldTimeSpan > 0;
}