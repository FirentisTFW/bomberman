#include "gameUI.h"

GameUI::GameUI(const int playersLives, const char color) {
    
    font.loadFromFile("images/fonts/BebasNeue-Regular.ttf");

    sideBarTexture.loadFromFile("images/UI/side_bar_game.png");
    sideBar.setTexture(sideBarTexture);
    sideBar.setPosition(800, 0);
   
    for(int i = 0; i < 4; i++) {
        charactersScores[i] = sf::Text("0", font);
        textProperties::setProperties(charactersScores[i], 25, 875, 116 + 140 * i);
    }
   
    for(int i = 0; i < 4; i++) {
        charactersLives[i] = sf::Text("1", font);
        textProperties::setProperties(charactersLives[i], 25, 847, 116 + 140 * i);
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
    textProperties::setProperties(overallScore, 35, 865, 615);

    pauseButton.setPosition(807, 675);
    pauseButton.setSize(sf::Vector2f(185, 50));
    pauseButton.setFillColor(sf::Color::White);

    pauseText = sf::Text("PAUSE", font);
    textProperties::setProperties(pauseText, 40, 855, 675);

    exitButton.setPosition(807, 736);
    exitButton.setSize(sf::Vector2f(185, 50));
    exitButton.setFillColor(sf::Color::White);

    exitText = sf::Text("EXIT", font);
    textProperties::setProperties(exitText, 40, 870, 736);
}

GameUI::~GameUI() {}

void GameUI::updateUI(std::vector<Character *> &characters, const int &playersScore){
    for (int i = 0; i < 4; i++)
        charactersScores[i].setString(std::to_string(characters[i]->score));
    setAndCenterOverallScore(playersScore);
}

void GameUI::setAndCenterOverallScore(const int &playersScore) {
    if (playersScore < 10)
        overallScore.setPosition(892, 615);
    else if (playersScore < 100)
        overallScore.setPosition(885, 615);
    else if (playersScore < 1000)
        overallScore.setPosition(878, 615);
    else if (playersScore < 10000)
        overallScore.setPosition(870, 615);

    overallScore.setString(std::to_string(playersScore));
}

void GameUI::drawUI(sf::RenderWindow* &window) {
    window->draw(sideBar);
    for(sf::Text score : charactersScores)
        window->draw(score);
    for(sf::Text lives : charactersLives)
        window->draw(lives);
    window->draw(overallScore);
    window->draw(pauseText);
    window->draw(exitText);
}