#pragma once
#include "init.h"

class GameUI {
    public:

        sf::Texture sideBarTexture;
        sf::Sprite sideBar;

        sf::Font font;

        std::array<sf::Text, 4> charactersScores;
        std::array<sf::Text, 4> charactersLives;

        GameUI();

        ~GameUI();

        void updateUI(sf::RenderWindow* &window);               // update side bar with stats
};