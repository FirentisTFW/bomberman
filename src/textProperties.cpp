#include "textProperties.h"

void textProperties::setProperties(sf::Text &text, int size, int posX, int posY) {
    text.setCharacterSize(size);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(posX, posY);
}

