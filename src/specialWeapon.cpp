#include "specialWeapon.h"

SpecialWeapon::SpecialWeapon(int _posX, int _posY, char _type) {

    posX = _posX;
    posY = _posY;
    type = _type;
    timeToDisappear = 120;

    if(type == 'f') {
        rect.setSize(sf::Vector2f(50, 50));
        rect.setPosition(posX * 50, posY * 50);
        rect.setFillColor(sf::Color::Yellow);
    }
}

SpecialWeapon::~SpecialWeapon() {}