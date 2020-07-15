#include "specialWeaponIcon.h"

Icon::Icon(int _posX, int _posY, char _color, sf::Texture &_texture, sf::Font &font) {
    posX = _posX;
    posY = _posY;
    color = _color;

    rect.setSize(sf::Vector2f(25, 25));
    rect.setPosition(posX * 50 + 10, posY * 50 - 30);
    rect.setFillColor(sf::Color::Green);

    setTexture(_texture);

    counter = sf::Text("1", font);
    counter.setCharacterSize(25);
    counter.setStyle(sf::Text::Bold);
    counter.setFillColor(sf::Color::White);
    counter.setOutlineThickness(1);
    counter.setOutlineColor(sf::Color::Black);
    counter.setPosition(rect.getPosition().x + 35, rect.getPosition().y -3);
}

void Icon::updatePosition(int _posX, int _posY, int _counter) {
    posX = _posX;
    posY = _posY;

    rect.setPosition(posX * 50 + 10, posY * 50 - 30);
    sprite.setPosition(rect.getPosition());

    counter.setString(std::to_string(_counter));
    counter.setPosition(rect.getPosition().x + 35, rect.getPosition().y - 3);
}

