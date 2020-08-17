#include "character.h"
#include "specialWeapon.h"

// ------------------------------------------ STATIC PROPERTIES -------------------------------------------------

std::array<float, 5> Character::movementSpeedFramerate = {5.0, 4.0, 3.0, 2.0, 1.0};

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

}

Character::~Character() {}

// ------------------------------------------ METHODS -------------------------------------------------


void Character::shouldCharacterMove(char direction, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    
    if(frozen) return;                                  // character can't move if frozen by another character

    if(animationTimer >= 3) {
        animationTimer = 0;
        sprite.setTextureRect(sf::IntRect(50 * animationCounter, 50 * animationDirection, 50, 50));
        animationCounter++;
        if(animationCounter >=4)
            animationCounter = 0;
    }

    const int newXPosition = getSuggestedXPosition(direction);
    const int newYPosition = getSuggestedYPosition(direction);

    if(lastDirection != direction && isHuman) {                 // player can change directions whenever he wants because he won't do it as fast as computer
        if(isMovePossible(newXPosition, newYPosition, direction, gameBoard, bombs))
            move(direction);
    }
    // TODO: different ways for player and AI
    else if(howManyFramesAfterMove >= Character::movementSpeedFramerate[speed-1]) {
        if (isMovePossible(newXPosition, newYPosition, direction, gameBoard, bombs)) {
            if(isHuman)
                move(direction);
            else {
                if (isMoveSafe(newXPosition, newYPosition, gameBoard, bombs))
                    move(direction);
            }
        }
    }

    lastTriedDirection = direction;
}

bool Character::isMovePossible(const int posX, const int posY, char direction, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    if(isPositionOnTheMap(posX, posY)) {
        if (gameBoard[posY][posX] != "box" && gameBoard[posY][posX] != "wall" && gameBoard[posY][posX] != "bomb" && gameBoard[posY][posX] != "ice") // field character wants to step on is possible to step on
            return true;
        if (gameBoard[posY][posX] == "bomb" && bombPushing == true)                            // character wants to step on the bomb and character can push the bombs
            return didCharacterPushBomb(posX, posY - 1, bombs, direction, gameBoard);
        return false;
    }
    return false;
}

bool Character::isMoveSafe(const int posX, const int posY, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    if (gameBoard[posY][posX] == "explosion" || gameBoard[posY][posX] == "fire")
        return false;

    std::vector<int> bombsPositionsVertical = AiBombChecker::getPositionOfClosestBombsVertical(posX, posY, gameBoard);
    std::vector<int> bombsPositionsHorizontal = AiBombChecker::getPositionOfClosestBombsHorizontal(posX, posY, gameBoard);

    // check bombs and their ranges
    bool isVerticalSafe = AiBombChecker::isVerticalDirectionSafe(posX, posY, bombsPositionsVertical, bombs);
    bool isHorizontalSafe = AiBombChecker::isHorizontalDirectionSafe(posX, posY, bombsPositionsHorizontal, bombs);

    return isVerticalSafe && isHorizontalSafe;
}

void Character::move(char direction) {
    switch(direction) {
        case 'u':
            if(posY > 0) {        // character can move -> still on the map
                rect.move(0, -50);
                sprite.move(0, -50);
                animationDirection = 3;
                posY--;
            }
            break;
        case 'd':
            if(posY < 15) {        
                rect.move(0, 50);
                sprite.move(0, 50);
                animationDirection = 0;
                posY++;
            }
            break;
        case 'l':
            if(posX > 0) {        
                rect.move(-50, 0);
                sprite.move(-50, 0);
                animationDirection = 2;
                posX--;
            }
            break;
        case 'r':
            if(posX < 15) {        
                rect.move(50, 0);
                sprite.move(50, 0);
                animationDirection = 1;
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

void Character::placeBomb(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard,std::vector<DiggedBomb*> &diggedBombs, std::vector<SpecialWeapon*> &specialWeapons, sf::Texture &bombTexture, std::array<sf::Texture, 2> &specialWeaponsTextures) {
    
    if(specialWeaponCounter > 0) {                  // character has a special weapon
        useSpecialWeapon(bombs, gameBoard, diggedBombs, specialWeapons, specialWeaponsTextures);
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

void Character::useSpecialWeapon(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<DiggedBomb *> &diggedBombs, std::vector<SpecialWeapon *> &specialWeapons, std::array<sf::Texture, 2> &specialWeaponsTextures) {
    
    if(specialWeapon == 'd') {          // digged bomb
        if (gameBoard[posY][posX] != "bomb" && gameBoard[posY][posX] != "digged_bomb") { // two bombs can't be placed on the same field
            diggedBombs.push_back(new DiggedBomb(posX, posY, color));
            gameBoard[posY][posX] = "digged_bomb";
            specialWeaponCounter--;
        }
    }
    else {
        std::string typeOfWeapon;
        if (specialWeapon == 'f')       // fire
            typeOfWeapon = "fire";
        else if (specialWeapon == 'i')    // ice
            typeOfWeapon = "ice";

        int addX, addY;                     
        switch(lastTriedDirection) {              // direction check
            case 'u':
                addX = 0;
                addY = -1;
                break;
            case 'd':
                addX = 0;
                addY = 1;
                break;
            case 'l':
                addX = -1;
                addY = 0;
                break;
            case 'r':
                addX = 1;
                addY = 0;
                break;
            default:
                break;
        }

        bool wasSpecialWeaponUsed = false;                                      // used to determine if you should decrease the weapon counter

        if(specialWeapon == 'f') {                                                      // FIRE
            if(Object::isPositionOnTheMap(posX + addX, posY + addY)) {
                if (gameBoard[posY + addY][posX + addX] != "wall") {
                    specialWeapons.push_back(new SpecialWeapon(posX + addX, posY + addY, specialWeapon, color, specialWeaponsTextures[0]));
                    gameBoard[posY + addY][posX + addX] = typeOfWeapon;
                    wasSpecialWeaponUsed = true;
                    if(Object::isPositionOnTheMap(posX + addX * 2, posY + addY * 2)) {
                        if (gameBoard[posY + addY * 2][posX + addX * 2] != "wall") {
                            specialWeapons.push_back(new SpecialWeapon(posX + addX * 2, posY + addY * 2, specialWeapon, color, specialWeaponsTextures[0]));
                            gameBoard[posY + addY * 2][posX + addX * 2] = typeOfWeapon;
                            if(Object::isPositionOnTheMap(posX + addX * 3, posY + addY * 3)) {
                                if (gameBoard[posY + addY * 3][posX + addX * 3] != "wall"){
                                    specialWeapons.push_back(new SpecialWeapon(posX + addX * 3, posY + addY * 3, specialWeapon, color, specialWeaponsTextures[0]));
                                    gameBoard[posY + addY * 3][posX + addX * 3] = typeOfWeapon;
                                }
                            }
                        }
                    }
                }
            }
        }
        else {                                                                          // ICE
            if(Object::isPositionOnTheMap(posX + addX, posY + addY)) {
                if (gameBoard[posY + addY][posX + addX] != "wall" && gameBoard[posY + addY][posX + addX] != "box") {
                    specialWeapons.push_back(new SpecialWeapon(posX + addX, posY + addY, specialWeapon, color, specialWeaponsTextures[1]));
                    gameBoard[posY + addY][posX + addX] = typeOfWeapon;
                    wasSpecialWeaponUsed = true;
                    if(Object::isPositionOnTheMap(posX + addX * 2, posY + addY * 2)) {
                        if (gameBoard[posY + addY * 2][posX + addX * 2] != "wall" && gameBoard[posY + addY * 2][posX + addX * 2] != "box") {
                            specialWeapons.push_back(new SpecialWeapon(posX + addX * 2, posY + addY * 2, specialWeapon, color, specialWeaponsTextures[1]));
                            gameBoard[posY + addY * 2][posX + addX * 2] = typeOfWeapon;
                            if(Object::isPositionOnTheMap(posX + addX * 3, posY + addY * 3)) {
                                if (gameBoard[posY + addY * 3][posX + addX * 3] != "wall" && gameBoard[posY + addY * 3][posX + addX * 3] != "box"){
                                    specialWeapons.push_back(new SpecialWeapon(posX + addX * 3, posY + addY * 3, specialWeapon, color, specialWeaponsTextures[1]));
                                    gameBoard[posY + addY * 3][posX + addX * 3] = typeOfWeapon;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (wasSpecialWeaponUsed)
            specialWeaponCounter--;
    }
}

void Character::steppedOnBonus(char type, int &playersLives, std::vector<Icon*> &specialWeaponsIcons, std::array<sf::Texture, 3> &iconsTextures, sf::Font &font) {
    switch(type) {                                                    // check bonus type                
        case 'r':
            range++;
            std::cout << "Range increased!" << std::endl;
            break;
        case 'b':
            bombLimit++;
            std::cout << "Bomb limit increased!" << std::endl;
            break;
        case 's':
            if(speed <5)                // 5 - maximal speed
                speed++;
            std::cout << "Speed increased!" << std::endl;
            break;
        case 'h':
            shield = true;
            std::cout << "Shield!" << std::endl;
            break;
        case 'l':
            std::cout << "Another live!" << std::endl;
            if (isHuman)
                playersLives++;
            break;  
        case 'p':
            std::cout << "Bomb pushing skill!" << std::endl;
            bombPushing = true;
            break;  

            // SPECIAL WEAPONS
        case 'f':
            std::cout << "Special weapon: fire!" << std::endl;
            specialWeapon = 'f';     
            specialWeaponCounter = 2;
            specialWeaponsIcons.push_back(new Icon(posX, posY, color, iconsTextures[0], font));
            break;
        case 'i':
            std::cout << "Special weapon: ice!" << std::endl;
            specialWeapon = 'i';     
            specialWeaponCounter = 1;
            specialWeaponsIcons.push_back(new Icon(posX, posY, color, iconsTextures[1], font));
            break;
        case 'd':
            std::cout << "Special weapon: digged bombs!" << std::endl;
            specialWeapon = 'd';     
            specialWeaponCounter = 2;
            specialWeaponsIcons.push_back(new Icon(posX, posY, color, iconsTextures[2], font));
            break;
        default:
            break;
    }
}