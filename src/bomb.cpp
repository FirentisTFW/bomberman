#include "bomb.h"

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Bomb::Bomb(int _posX, int _posY, int _range, char _color, int *_charactersBombLimit) {

    range = _range;
    color = _color;
    timeToExplode = 180;                        // 3 seconds
    posX = _posX;
    posY = _posY;

    movingBombTimer = -1;
    charactersBombLimit = _charactersBombLimit;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::White);
}

Bomb::~Bomb() {}

// ------------------------------------------ METHODS -------------------------------------------------

void Bomb::explode(std::vector<Explosion*> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    
    std::cout << "Explosion!" << std::endl;

    explosions.push_back(new Explosion(posX, posY, color));

    for(int i=0; i<range; i++) {                             // DOWN
        if (posY + (i + 1) > 15)                             // explosion can't get outside of the map
            break; 
        explosions.push_back(new Explosion(posX, posY + (i + 1), color));

        // if there is a bomb or box on the way, stop exploding in this direction, updateGameBoard() method in Game class will check if the explosion should destroy this object or not
        if (gameBoard[posY + (i + 1)][posX] == "bomb" || gameBoard[posY + (i + 1)][posX] == "box" || gameBoard[posY + (i + 1)][posX] == "wall")
            break;
    }
    for(int i=0; i<range; i++) {                           // UP
        if (posY - (i + 1) < 0)                          
            break;
        explosions.push_back(new Explosion(posX, posY - (i + 1), color));
        if (gameBoard[posY - (i + 1)][posX] == "bomb" || gameBoard[posY - (i + 1)][posX] == "box" || gameBoard[posY - (i + 1)][posX] == "wall")
            break;
    }
    for(int i=0; i<range; i++) {                            // RIGHT
        if (posX + (i + 1) > 15)                           
            break;
        explosions.push_back(new Explosion(posX+(i+1), posY, color));
        if (gameBoard[posY][posX + (i + 1)] == "bomb" || gameBoard[posY][posX + (i + 1)] == "box" || gameBoard[posY][posX + (i + 1)] == "wall")
            break;
    }
    for(int i=0; i<range; i++) {                            // LEFT
        if (posX - (i + 1) < 0)                         
            break;
        explosions.push_back(new Explosion(posX - (i + 1), posY, color));
        if (gameBoard[posY][posX - (i + 1)] == "bomb" || gameBoard[posY][posX - (i + 1)] == "box" || gameBoard[posY][posX - (i + 1)] == "wall")
            break;
    }

    *charactersBombLimit += 1;                                                  // bomb exploded so the character can place a new bomb

    std::cout << "bombs limit: " << *charactersBombLimit << std::endl;
}

bool Bomb::moveBomb(char _direction, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    int addX, addY;
    std::cout << posY << std::endl;

    direction = _direction;

    switch(direction){                                                          // check the rolling bomb's direction
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
    if(Object::isPositionOnTheMap(posX + addX, posY + addY)) {           // still on the map
        if (gameBoard[posY + addY][posX + addX] == "0" || gameBoard[posY + addY][posX + addX] == "bonus") {                 // bomb can roll there, the field is empty
            posX += addX;
            posY += addY;
            rect.setPosition(posX * 50, posY * 50);
            gameBoard[posY][posX] = "bomb";
            movingBombTimer = 6;                                       // speed: 10 fields for one second (60 frames / 6)

            return true;
        }
    }
    movingBombTimer = -1;
    timeToExplode = 0;
    return false;
}

void Bomb::checkBombsTimers(std::vector<Bomb*> &bombs, std::vector<Explosion*> &explosions,std::array<std::array<std::string, 16>, 16> &gameBoard) {
    int bombsSize = bombs.size();
    for(int i = 0; i < bombsSize; i++) {
        if(bombs[i]->movingBombTimer == -1) {                                   // bomb is not moving
            bombs[i]->timeToExplode--;
            if(bombs[i]->timeToExplode <= 0) {
                bombs[i]->explode(explosions, gameBoard);
                bombs.erase(bombs.begin() + i);
                bombsSize = bombs.size();
                i--;
            }
        }
        else {                                                                  // bomb is moving
            bombs[i]->movingBombTimer--;
            if(bombs[i]->movingBombTimer <= 0 ) {
                bombs[i]->moveBomb(bombs[i]->direction, gameBoard);
            }
        }
    }
}
