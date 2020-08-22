#pragma once
#include "character.h"
#include "textProperties.h"

class GameUI {
    private:
        sf::Texture sideBarTexture;
        sf::Sprite sideBar;
        sf::Text overallScore;                              // player's overall score
        sf::Text pauseText;
        sf::Text exitText;
        std::array<sf::Text, 4> charactersScores;
        std::array<sf::Text, 4> charactersLives;

        void setAndCenterOverallScore(const int &playersScore);

    public:
        sf::Font font;
        sf::RectangleShape pauseButton;                       
        sf::RectangleShape exitButton;

        GameUI(const int playersLives, const char color);

        ~GameUI();

        void updateUI(std::vector<Character *> &characters, const int &playersScore);       // update side bar with stats

        void drawUI(sf::RenderWindow* &window);                                             // draw side bar
};