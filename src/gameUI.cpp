#include "gameUI.h"

GameUI::GameUI(const int playersLives, const char color) {
    
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
        charactersLives[i].setPosition(847, 116 + 140 * i);
    }

    switch(color) {
        case 'b':
            charactersLives[0].setString(std::to_string(playersLives));
            break;
        case 'g':
            charactersLives[1].setString(std::to_string(playersLives));
            break;
        case 'r':
            charactersLives[2].setString(std::to_string(playersLives));
            break;
        case 'y':
            charactersLives[3].setString(std::to_string(playersLives));
            break;
        default:
            break;
    }

    overallScore = sf::Text("0", font);
    overallScore.setCharacterSize(35);
    overallScore.setStyle(sf::Text::Bold);
    overallScore.setFillColor(sf::Color::White);
    overallScore.setOutlineThickness(1);
    overallScore.setOutlineColor(sf::Color::Black);
    overallScore.setPosition(865, 615);

    pauseRect.setPosition(807, 675);
    pauseRect.setSize(sf::Vector2f(185, 50));
    pauseRect.setFillColor(sf::Color::White);

    pauseText = sf::Text("PAUSE", font);
    pauseText.setCharacterSize(40);
    pauseText.setStyle(sf::Text::Bold);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setOutlineThickness(1);
    pauseText.setOutlineColor(sf::Color::Black);
    pauseText.setPosition(855, 675);

    exitRect.setPosition(807, 736);
    exitRect.setSize(sf::Vector2f(185, 50));
    exitRect.setFillColor(sf::Color::White);

    exitText = sf::Text("EXIT", font);
    exitText.setCharacterSize(40);
    exitText.setStyle(sf::Text::Bold);
    exitText.setFillColor(sf::Color::White);
    exitText.setOutlineThickness(1);
    exitText.setOutlineColor(sf::Color::Black);
    exitText.setPosition(870, 736);
}

GameUI::~GameUI() {}

void GameUI::drawUI(sf::RenderWindow* &window) {
    window->draw(sideBar);
    // window->draw(charactersScores[0]);
    for(sf::Text score : charactersScores) {
        window->draw(score);
    }
    for(sf::Text lives : charactersLives) {
        window->draw(lives);
    }
    window->draw(overallScore);
    window->draw(pauseText);
    window->draw(exitText);
}

void GameUI::updateUI(std::vector<Character *> &characters, const int &playersScore){

    for (int i = 0; i < 4; i++) {
        charactersScores[i].setString(std::to_string(characters[i]->score));
    }

    // centering the text with the score (dependent on the score's length)
    if(playersScore < 10)   overallScore.setPosition(892, 615);
    else if(playersScore < 100)   overallScore.setPosition(885, 615);
    else if(playersScore < 1000)   overallScore.setPosition(878, 615);
    else if(playersScore < 10000)   overallScore.setPosition(870, 615);

    overallScore.setString(std::to_string(playersScore));
}
