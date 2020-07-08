#include "gameUI.h"

GameUI::GameUI() {
    
    font.loadFromFile("images/fonts/BebasNeue-Regular.ttf");

    sideBarTexture.loadFromFile("images/UI/side_bar_game.png");
    sideBar.setTexture(sideBarTexture);
    sideBar.setPosition(800, 0);
   
    for(int i = 0; i < 4; i++) {
        charactersScores[i] = sf::Text("0", font);
        charactersScores[i].setCharacterSize(25);
        charactersScores[i].setStyle(sf::Text::Bold);
        charactersScores[i].setFillColor(sf::Color::White);
        charactersScores[i].setOutlineThickness(1);
        charactersScores[i].setOutlineColor(sf::Color::Black);
        charactersScores[i].setPosition(875, 116 + 140 * i);
    }
   
    for(int i = 0; i < 4; i++) {
        charactersLives[i] = sf::Text("1", font);
        charactersLives[i].setCharacterSize(25);
        charactersLives[i].setStyle(sf::Text::Bold);
        charactersLives[i].setFillColor(sf::Color::White);
        charactersLives[i].setOutlineThickness(1);
        charactersLives[i].setOutlineColor(sf::Color::Black);
        charactersLives[i].setPosition(845, 116 + 140 * i);
    }
}

GameUI::~GameUI() {}

void GameUI::updateUI(sf::RenderWindow* &window) {
    window->draw(sideBar);
    // window->draw(charactersScores[0]);
    for(sf::Text score : charactersScores) {
        window->draw(score);
    }
    for(sf::Text lives : charactersLives) {
        window->draw(lives);
    }
}