#pragma once

#include "init.h"

class GameTextures {
    private:
        void loadCharactersTextures();

        void loadBoxesTextures();

        void loadSpecialWeaponsTextures();

        void loadBonusesTextures();

        void loadIconsTextures();

    public:
        sf::Texture backgroundTexture;
        std::array<sf::Texture, 4> charactersTextures;
        std::array<sf::Texture, 10> boxesTextures;
        std::array<sf::Texture, 2> specialWeaponsTextures; // 0 fire, 1 - ice
        std::array<sf::Texture, 3> iconsTextures;          // 0 fire, 1 - ice, 2 - digged bomb
        std::array<sf::Texture, 9> bonusesTextures;
        sf::Texture bombTexture;
        sf::Texture explosionTexture;

        GameTextures();

        ~GameTextures();

        void loadTextures();
};