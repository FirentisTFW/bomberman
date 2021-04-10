#include "includes/characterEditor.h"

CharacterEditor::CharacterEditor(bool _isHuman, int _posX, int _posY, char _color) {

    isHuman = _isHuman;
    posX = _posX;
    posY = _posY;
    color = _color;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::Green);
}

CharacterEditor::~CharacterEditor() {}
