#include "box.h"

Box::Box(bool _isDestroyable, int _posX, int _posY) {
    isDestroyable = _isDestroyable;
    posX = _posX;
    posY = _posY;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::Red);
}

Box::~Box() {}