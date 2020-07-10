#include "specialWeapon.h"

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
    else {
        rect.setSize(sf::Vector2f(50, 50));
        rect.setPosition(posX * 50, posY * 50);
        rect.setFillColor(sf::Color::White);
    }

    setTexture(texture);

    if(type == 'f') sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));   // FIRE - START ANIMATION
}

SpecialWeapon::~SpecialWeapon() {}