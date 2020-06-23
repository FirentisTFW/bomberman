#include "character.h"

// ------------------------------------------ STATIC PROPERTIES -------------------------------------------------

std::array<float, 5> Character::movementSpeedFramerate = {5.0, 4.0, 3.0, 2.0, 1.0};

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Character::Character(bool _isHuman, int _posX, int _posY, char _color) {
    std::cout << "character created!" << std::endl;

    isHuman = _isHuman;
    speed = 1;
    bombLimit = 200;
    shield = false;

    posX = _posX;
    posY = _posY;
    color = _color;
    howManyFramesAfterMove = 0;
    lastDirection = ' ';

    range = 2;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::Green);

}

Character::~Character() {}

// ------------------------------------------ METHODS -------------------------------------------------


void Character::shouldCharacterMove(char direction, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    
    howManyFramesAfterMove++;  

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
}

bool Character::isMovePossible(char direction, const std::array<std::array<std::string, 16>, 16> &gameBoard) {

     switch(direction) {
        case 'u':
            if(posY > 0) {        // character can move -> still on the map
                if(gameBoard[posY-1][posX] == "0" || gameBoard[posY-1][posX] == "bonus" || gameBoard[posY-1][posX] == "explosion") {    // field character wants to step on is possible to step on
                    return true;
                }
                return false;
            }
            break;
        case 'd':
            if(posY < 15) {        // character can move -> still on the map
                if(gameBoard[posY+1][posX] == "0" || gameBoard[posY+1][posX] == "bonus" || gameBoard[posY+1][posX] == "explosion") {
                    return true;
                }
                return false;
            }
            break;
        case 'l':
            if(posX > 0) {        // character can move -> still on the map
                if(gameBoard[posY][posX-1] == "0" || gameBoard[posY][posX-1] == "bonus" || gameBoard[posY][posX-1] == "explosion") {
                    return true;
                }
                return false;
            }
            break;
        case 'r':
            // std::cout << "move right" << std::endl;
            if(posX < 15) {        // character can move -> still on the map
                if(gameBoard[posY][posX+1] == "0" || gameBoard[posY][posX+1] == "bonus" || gameBoard[posY][posX+1] == "explosion") {
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

void Character::placeBomb(std::vector<Bomb *> &bombs, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    if(bombLimit > 0) {
        if(gameBoard[posY][posX] != "bomb") {                                   // two bombs can't be placed on the same field
            bombLimit--;
            bombs.push_back(new Bomb(posX, posY, range, color));
            gameBoard[posY][posX] = "bomb";
        }
    }
}