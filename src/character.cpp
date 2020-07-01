#include "character.h"
#include "specialWeapon.h"

// ------------------------------------------ STATIC PROPERTIES -------------------------------------------------

std::array<float, 5> Character::movementSpeedFramerate = {5.0, 4.0, 3.0, 2.0, 1.0};

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Character::Character(bool _isHuman, int _posX, int _posY, char _color) {
    std::cout << "character created!" << std::endl;

    isHuman = _isHuman;
    speed = 1;
    bombLimit = 1;
    shield = false;
    lostShieldTimeSpan = 0;
    frozen = false;
    frozenTime = 0;

    posX = _posX;
    posY = _posY;
    color = _color;
    howManyFramesAfterMove = 0;
    lastDirection = ' ';
    lastTriedDirection = ' ';

    range = 2;
    specialWeapon = '0';                  
    specialWeaponCounter = 0;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::Green);

}

Character::~Character() {}

// ------------------------------------------ METHODS -------------------------------------------------


void Character::shouldCharacterMove(char direction, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    
    howManyFramesAfterMove++;  

    if(frozen) return;

    if(lastDirection != direction) {
        if(isMovePossible(direction, gameBoard)) {
            move(direction);
            howManyFramesAfterMove = 0;
        }
    }
    else if(howManyFramesAfterMove >= Character::movementSpeedFramerate[speed-1]) {
        if (isMovePossible(direction, gameBoard)) {
            howManyFramesAfterMove = 0;
            move(direction);
        }
    }

    lastTriedDirection = direction;
}

bool Character::isMovePossible(char direction, const std::array<std::array<std::string, 16>, 16> &gameBoard) {

     switch(direction) {
        case 'u':
            if(posY > 0) {        // character can move -> still on the map
                // if(gameBoard[posY-1][posX] == "0" || gameBoard[posY-1][posX] == "bonus" || gameBoard[posY-1][posX] == "explosion") {    // field character wants to step on is possible to step on
                if(gameBoard[posY-1][posX] != "box" && gameBoard[posY-1][posX] != "wall") {    // field character wants to step on is possible to step on
                    return true;
                }
                return false;
            }
            break;
        case 'd':
            if(posY < 15) {        // character can move -> still on the map
                if(gameBoard[posY+1][posX] != "box" && gameBoard[posY+1][posX] != "wall") {
                    return true;
                }
                return false;
            }
            break;
        case 'l':
            if(posX > 0) {        // character can move -> still on the map
                if(gameBoard[posY][posX-1] != "box" && gameBoard[posY][posX-1] != "wall") {
                    return true;
                }
                return false;
            }
            break;
        case 'r':
            // std::cout << "move right" << std::endl;
            if(posX < 15) {        // character can move -> still on the map
                if(gameBoard[posY][posX+1] != "box" && gameBoard[posY][posX+1] != "wall") {
                    return true;
                }
                return false;
            }
            break;
        default:
            return false;
            break;
    }
}

void Character::move(char direction) {
    switch(direction) {
        case 'u':
            if(posY > 0) {        // character can move -> still on the map
                rect.move(0, -50);
                posY--;
            }
            break;
        case 'd':
            if(posY < 15) {        // character can move -> still on the map
                rect.move(0, +50);
                posY++;
            }
            break;
        case 'l':
            if(posX > 0) {        // character can move -> still on the map
                rect.move(-50, 0);
                posX--;
            }
            break;
        case 'r':
            // std::cout << "move right" << std::endl;
            if(posX < 15) {        // character can move -> still on the map
                rect.move(50, 0);
                posX++;
            }
            break;
        default:
            break;
    }
    lastDirection = direction;
}

void Character::placeBomb(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard,std::vector<DiggedBomb*> &diggedBombs, std::vector<SpecialWeapon*> &specialWeapons) {
    
    if(specialWeaponCounter > 0) {                  // character has a special weapon
        useSpecialWeapon(bombs, gameBoard, diggedBombs, specialWeapons);
        return;
    }

    if(bombLimit > 0) {
        if(gameBoard[posY][posX] != "bomb" && gameBoard[posY][posX] != "digged_bomb") {                                   // two bombs can't be placed on the same field
            bombLimit--;
            bombs.push_back(new Bomb(posX, posY, range, color, &bombLimit));
            gameBoard[posY][posX] = "bomb";
        }
    }
}

void Character::useSpecialWeapon(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<DiggedBomb *> &diggedBombs, std::vector<SpecialWeapon *> &specialWeapons) {
    
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

        if(specialWeapon == 'f') {
            if (gameBoard[posY + addY][posX + addX] != "wall") {
                specialWeapons.push_back(new SpecialWeapon(posX + addX, posY + addY, specialWeapon));
                gameBoard[posY + addY][posX + addX] = typeOfWeapon;
                if (gameBoard[posY + addY * 2][posX + addX * 2] != "wall") {
                    specialWeapons.push_back(new SpecialWeapon(posX + addX * 2, posY + addY * 2, specialWeapon));
                    gameBoard[posY + addY * 2][posX + addX * 2] = typeOfWeapon;
                    if (gameBoard[posY + addY * 3][posX + addX * 3] != "wall"){
                        specialWeapons.push_back(new SpecialWeapon(posX + addX * 3, posY + addY * 3, specialWeapon));
                        gameBoard[posY + addY * 3][posX + addX * 3] = typeOfWeapon;
                    }
                }
            }
        }
        else {
            if (gameBoard[posY + addY][posX + addX] != "wall" && gameBoard[posY + addY][posX + addX] != "box") {
                specialWeapons.push_back(new SpecialWeapon(posX + addX, posY + addY, specialWeapon));
                gameBoard[posY + addY][posX + addX] = typeOfWeapon;
                if (gameBoard[posY + addY * 2][posX + addX * 2] != "wall" && gameBoard[posY + addY * 2][posX + addX * 2] != "box") {
                    specialWeapons.push_back(new SpecialWeapon(posX + addX * 2, posY + addY * 2, specialWeapon));
                    gameBoard[posY + addY * 2][posX + addX * 2] = typeOfWeapon;
                    if (gameBoard[posY + addY * 3][posX + addX * 3] != "wall" && gameBoard[posY + addY * 3][posX + addX * 3] != "box"){
                        specialWeapons.push_back(new SpecialWeapon(posX + addX * 3, posY + addY * 3, specialWeapon));
                        gameBoard[posY + addY * 3][posX + addX * 3] = typeOfWeapon;
                    }
                }
            }
        }
        specialWeaponCounter--;
    }
}

void Character::steppedOnBonus(char type, int &playersLives) {
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

            // SPECIAL WEAPONS
        case 'f':
            std::cout << "Special weapon: fire!" << std::endl;
            specialWeapon = 'f';     
            specialWeaponCounter = 2;
            break;
        case 'i':
            std::cout << "Special weapon: ice!" << std::endl;
            specialWeapon = 'i';     
            specialWeaponCounter = 1;
            break;
        case 'd':
            std::cout << "Special weapon: digged bombs!" << std::endl;
            specialWeapon = 'd';     
            specialWeaponCounter = 2;
            break;
        default:
            break;
    }
}