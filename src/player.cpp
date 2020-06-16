#include "player.h"

// ------------------------------------------ STATIC PROPERTIES -------------------------------------------------

std::array<float, 5> Player::movementSpeedFramerate = {5.0, 4.0, 3.0, 2.0, 1.0};

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Player::Player(bool _isHuman, int _posX, int _posY) {
    std::cout << "player created!" << std::endl;

    lives = 3;
    speed = 1;
    posX = _posX;
    posY = _posY;
    howManyFramesAfterMove = 0;
    lastDirection = ' ';

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::Green);

    if(_isHuman == true) isHuman = true;


}

Player::~Player() {};

// ------------------------------------------ METHODS -------------------------------------------------

void Player::shouldPlayerMove(char direction) {
    howManyFramesAfterMove++;                           
    if(lastDirection != direction) {
        move(direction);
        howManyFramesAfterMove = 0;
    }
    else if(howManyFramesAfterMove >= Player::movementSpeedFramerate[speed-1]) {
        howManyFramesAfterMove = 0;
        move(direction);
    }
}

void Player::move(char direction) {
    switch(direction) {
        case 'u':
            if(posY > 0) {        // player can move -> still on the map
                rect.move(0, -50);
                posY--;
            }
            break;
        case 'd':
            if(posY < 15) {        // player can move -> still on the map
                rect.move(0, +50);
                posY++;
            }
            break;
        case 'l':
            if(posX > 0) {        // player can move -> still on the map
                rect.move(-50, 0);
                posX--;
            }
            break;
        case 'r':
            // std::cout << "move right" << std::endl;
            if(posX < 15) {        // player can move -> still on the map
                rect.move(50, 0);
                posX++;
            }
            break;
        default:
            break;
    }
    lastDirection = direction;
}