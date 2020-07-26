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

        void putAssetOnMap(sf::Vector2f mousePosition, sf::Texture &texture);

        void makeFieldEmpty(const int posX, const int posY);

        void checkWhatAssetIsOnPosition(const int posX,const  int posY);

        void removeBoxFromPosition(const int _posX, const int _posY);

        void removeCharacterFromPosition(const int _posX, const int _posY);

        void draw();
};