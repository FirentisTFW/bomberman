#pragma once
#include "specialWeapon.h"

class Icon : public Object {
    public:

        sf::Text counter;
        char color;

        Icon(int _posX, int _posY, char _color, sf::Texture &_texture, sf::Font &font);

        ~Icon();

        void updatePosition(int _posX, int _posY, int _counter);
};