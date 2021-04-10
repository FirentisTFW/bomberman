#include "includes/textProperties.h"

void textProperties::setProperties(sf::Text &text, int size, int posX, int posY) {
    text.setCharacterSize(size);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(posX, posY);
}

void textProperties::setLetterSpacing(sf::Text &text, int numberOfSpaces) {
    std::string oldString = text.getString();
    std::string newString = "";
    for (char &c : oldString ) {
        newString += c;
        for(int j = 0; j < numberOfSpaces; j++)
            newString += " ";
    }
    text.setString(newString);
}