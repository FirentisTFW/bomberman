#include "includes/specialWeapon.h"

SpecialWeapon::SpecialWeapon(int _posX, int _posY, char _type, char _color, sf::Texture &texture) {

    posX = _posX;
    posY = _posY;
    type = _type;
    color = _color;
    timeToDisappear = 120;
    animationCounter = 0;

    if(type == 'f') {
        rect.setSize(sf::Vector2f(50, 50));
        rect.setPosition(posX * 50, posY * 50);
        rect.setFillColor(sf::Color::Yellow);
    }
    else {                                      // 'i'
        rect.setSize(sf::Vector2f(50, 50));
        rect.setPosition(posX * 50, posY * 50);
        rect.setFillColor(sf::Color::White);
    }

    setTexture(texture);

    if(type == 'f') sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));   // FIRE - START ANIMATION
}

SpecialWeapon::~SpecialWeapon() {}

bool SpecialWeapon::canYouDigBombHere(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    return gameBoard[posY][posX] != "bomb" && gameBoard[posY][posX] != "digged_bomb";
}

bool SpecialWeapon::canFireBeUsedHere(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    return isPositionOnTheMap(posX, posY) && gameBoard[posY][posX] != "wall";
}

bool SpecialWeapon::canIceBeUsedHere(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    return isPositionOnTheMap(posX, posY) && gameBoard[posY][posX] != "wall" && gameBoard[posY][posX] != "box";
}

int SpecialWeapon::getXSummand(const char direction) {
    if(direction == 'l')
        return -1;
    if(direction == 'r')
        return 1;
    return 0;
}

int SpecialWeapon::getYSummand(const char direction) {
    if (direction == 'u')
        return -1;
    if (direction == 'd')
        return 1;
    return 0;
}