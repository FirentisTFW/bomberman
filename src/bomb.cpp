#include "bomb.h"

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Bomb::Bomb(int _posX, int _posY, int _range, char _color, int *_charactersBombLimit) {

    range = _range;
    color = _color;
    timeToExplode = 180;                        // 3 seconds
    posX = _posX;
    posY = _posY;

    animationCounter = 0;
    animationDirectionUp = true;

    movingBombTimer = -1;
    charactersBombLimit = _charactersBombLimit;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::White);
}

Bomb::~Bomb() {}

// ------------------------------------------ METHODS -------------------------------------------------

void Bomb::explode(std::vector<Explosion*> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard,  sf::Texture &explosionTexture) {
    
    explosions.push_back(new Explosion(posX, posY, color, explosionTexture));

    makeExplosionsInDirection('u', explosions, gameBoard, explosionTexture);
    makeExplosionsInDirection('d', explosions, gameBoard, explosionTexture);
    makeExplosionsInDirection('l', explosions, gameBoard, explosionTexture);
    makeExplosionsInDirection('r', explosions, gameBoard, explosionTexture);

    *charactersBombLimit += 1;                                                  // bomb exploded so the character can place a new bomb

    // std::cout << "bombs limit: " << *charactersBombLimit << std::endl;
}

void Bomb::makeExplosionsInDirection(const char direction, std::vector<Explosion *> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard, sf::Texture &explosionTexture) {
    int xMultiplier = getXMultiplierForExplosion(direction);
    int yMultiplier = getYMultiplierForExplosion(direction);
    for(int i=1; i<=range; i++) {                             
        if (isPositionOnTheMap(posX + i * xMultiplier, posY + i * yMultiplier)) {
            explosions.push_back(new Explosion(posX + i * xMultiplier, posY + i * yMultiplier, color, explosionTexture));

            // if there is a bomb or box on the way, stop exploding in this direction, updateGameBoard() method in Game class will check if the explosion should destroy this object or not
            if (gameBoard[posY + i * yMultiplier][posX + i * xMultiplier] == "bomb" || gameBoard[posY + i * yMultiplier][posX + i * xMultiplier] == "box" || gameBoard[posY + i * yMultiplier][posX + i * xMultiplier] == "wall")
                break;
        }
    }
}

int Bomb::getXMultiplierForExplosion(const char direction) {
    if(direction == 'u')
        return 0;
    if(direction == 'd')
        return 0;
    if(direction == 'l')
        return -1;
    return 1;           // 'r'
}

int Bomb::getYMultiplierForExplosion(const char direction) {
    if(direction == 'u')
        return -1;
    if(direction == 'd')
        return 1;
    if(direction == 'l')
        return 0;
    return 0;           // 'r'
}

bool Bomb::moveBomb(char _direction, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    if(movingBombTimer != -1)                                                   // bomb is already moving
        return false;

    int addX, addY;
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
            sprite.setPosition(rect.getPosition());
            gameBoard[posY][posX] = "bomb";
            movingBombTimer = 6;                                       // speed: 10 fields for one second (60 frames / 6)
            return true;
        }
    }
    movingBombTimer = -1;
    timeToExplode = 0;
    return false;
}

void Bomb::checkBombsTimers(std::vector<Bomb*> &bombs, std::vector<Explosion*> &explosions,std::array<std::array<std::string, 16>, 16> &gameBoard, sf::Texture &explosionTexture) {
    int bombsSize = bombs.size();
    for(int i = 0; i < bombsSize; i++) {
        if(bombs[i]->movingBombTimer == -1) {                                   // bomb is not moving
            bombs[i]->timeToExplode--;
            if(bombs[i]->timeToExplode <= 0) {
                bombs[i]->explode(explosions, gameBoard, explosionTexture);
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
