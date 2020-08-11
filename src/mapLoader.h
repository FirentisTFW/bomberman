#pragma once
#include "box.h"
#include "character.h"

class MapLoader {
    private:
        std::fstream mapFile;

        void loadBackground(sf::Texture &backgroundTexture);

        void loadBoxes(std::vector<Box *> &boxes, std::array<sf::Texture, 10> &boxesTextures);

        void loadCharacters(std::vector<Character *> &characters, std::array<sf::Texture, 4> &charactersTextures);

        int getCounter(const std::string line);

    public:
        MapLoader();

        ~MapLoader();

        void loadMap(std::vector<Box *> &boxes, std::vector<Character *> &characters, std::array<sf::Texture, 10> &boxesTextures, std::array<sf::Texture, 4> &charactersTextures, sf::Texture &backgroundTexture);
};