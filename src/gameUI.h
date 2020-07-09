#pragma once
#include "character.h"

class GameUI {
    public:

        sf::Texture sideBarTexture;
        sf::Sprite sideBar;

        sf::Font font;

        sf::Text overallScore;                              // player's overall score
        sf::Text pauseText;
        sf::Text exitText;

        // buttons for collision
        sf::RectangleShape pauseRect;                       
        sf::RectangleShape exitRect;

        std::array<sf::Text, 4> charactersScores;
        std::array<sf::Text, 4> charactersLives;

        GameUI(const int playersLives, const char color);

        ~GameUI();

        void drawUI(sf::RenderWindow* &window);                                             // draw side bar

        void updateUI(std::vector<Character *> &characters, const int &playersScore);       // update side bar with stats
};