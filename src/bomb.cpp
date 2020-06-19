#include "bomb.h"

// ------------------------------------------ CONSTRUCTORS -------------------------------------------------

Bomb::Bomb(int _posX, int _posY, int _range, char _color) {

    range = _range;
    color = _color;
    timeToExplode = 180;
    posX = _posX;
    posY = _posY;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::White);
}

Bomb::~Bomb() {}

// ------------------------------------------ METHODS -------------------------------------------------

void Bomb::explode(std::vector<Explosion*> &explosions, std::array<std::array<std::string, 16>, 16> &gameBoard) {
    
    std::cout << "Explosion!" << std::endl;

    // CREATE EXPLOSION IN BOMB POSITION
    explosions.push_back(new Explosion(posX, posY, color));

    // HERE SHOULD BE FUNCTION CHECKING COLLISION!

    for(int i=0; i<range; i++) {
        explosions.push_back(new Explosion(posX, posY + (i + 1), color));
        if(gameBoard[posY + (i+1)][posX] == "bomb")
            break;
        if(gameBoard[posY + (i+1)][posX] == "box")
            break;
    }
    for(int i=0; i<range; i++) {
        explosions.push_back(new Explosion(posX, posY - (i + 1), color));
        if (gameBoard[posY - (i + 1)][posX] == "bomb")
            break;
        if (gameBoard[posY - (i + 1)][posX] == "box")
            break;
    }
    for(int i=0; i<range; i++) {
        explosions.push_back(new Explosion(posX+(i+1), posY, color));
        if (gameBoard[posY][posX + (i + 1)] == "bomb")
            break;
        if (gameBoard[posY][posX + (i + 1)] == "box")
            break;
    }
    for(int i=0; i<range; i++) {
        explosions.push_back(new Explosion(posX - (i + 1), posY, color));
        if (gameBoard[posY][posX - (i + 1)] == "bomb")
            break;
        if (gameBoard[posY][posX - (i + 1)] == "box")
            break;
    }
}

void Bomb::checkBombsTimers(std::vector<Bomb*> &bombs, std::vector<Explosion*> &explosions,std::array<std::array<std::string, 16>, 16> &gameBoard) {
    // std::cout << explosions.size() << std::endl;
    int bombsSize = bombs.size();
    for(int i = 0; i < bombsSize; i++) {
        bombs[i]->timeToExplode--;
        if(bombs[i]->timeToExplode <= 0) {
            bombs[i]->explode(explosions, gameBoard);
            bombs.erase(bombs.begin() + i);
            bombsSize = bombs.size();
            i--;
        }
    }
}
