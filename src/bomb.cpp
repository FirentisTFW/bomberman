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

    explosions.push_back(new Explosion(posX, posY, color));

    for(int i=0; i<range; i++) {                             // DOWN
        if (posY + (i + 1) > 15)                             // explosion can't get outside of the map
            break; 
        explosions.push_back(new Explosion(posX, posY + (i + 1), color));

        // if there is a bomb or box on the way, stop exploding in this direction, updateGameBoard() method in Game class will check if the explosion should destroy this object or not
        if (gameBoard[posY + (i + 1)][posX] == "bomb" || gameBoard[posY + (i + 1)][posX] == "box") 
            break;
    }
    for(int i=0; i<range; i++) {                           // UP
        if (posY - (i + 1) < 0)                          
            break;
        explosions.push_back(new Explosion(posX, posY - (i + 1), color));
        if (gameBoard[posY - (i + 1)][posX] == "bomb" || gameBoard[posY - (i + 1)][posX] == "box")
            break;
    }
    for(int i=0; i<range; i++) {                            // RIGHT
        if (posX + (i + 1) > 15)                           
            break;
        explosions.push_back(new Explosion(posX+(i+1), posY, color));
        if (gameBoard[posY][posX + (i + 1)] == "bomb" || gameBoard[posY][posX + (i + 1)] == "box")
            break;
    }
    for(int i=0; i<range; i++) {                            // LEFT
        if (posY - (i + 1) < 0)                         
            break;
        explosions.push_back(new Explosion(posX - (i + 1), posY, color));
        if (gameBoard[posY][posX - (i + 1)] == "bomb" || gameBoard[posY][posX - (i + 1)] == "box")
            break;
    }
}

void Bomb::checkBombsTimers(std::vector<Bomb*> &bombs, std::vector<Explosion*> &explosions,std::array<std::array<std::string, 16>, 16> &gameBoard) {
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
