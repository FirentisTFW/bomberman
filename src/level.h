#pragma once
#include "levelEditorUI.h"

class Level {

    public:
        sf::RenderWindow* window;

        std::array<std::array<std::string, 16>, 16> gameBoard;
        sf::Sprite background;
        std::string chosenAsset;
        
        std::vector<Box *> boxes;
        std::vector<Character *> characters;

        Level(sf::RenderWindow* _window);

        ~Level();

        void assetWasChosen(std::string assetName);

        void putAssetOnMap(sf::Vector2f mousePosition);

        void draw();
};