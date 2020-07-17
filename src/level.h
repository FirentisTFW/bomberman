#pragma once
#include "levelEditorUI.h"

class Level {

    public:
        std::array<std::array<std::string, 16>, 16> gameBoard;

        sf::Sprite background;

        std::vector<Box *> boxes;
        std::vector<Character *> characters;

    Level();
    
    ~Level();

};