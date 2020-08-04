#include "mainMenu.h"

std::array<std::string, 6> MainMenu::stringsForButtonsTexts = {"Start game", "Load game", "Level editor", "Highscores", "Credits", "Exit"};

MainMenu::MainMenu(sf::RenderWindow * _window) {
    window = _window;

    setBackground();
    loadFont();
    loadTitle();
    loadButtons();
    loadTexts();
}

MainMenu::~MainMenu() {}

void MainMenu::setBackground() {
    setBackgroundTexture();
    background.setPosition(0, 0);
    background.setTexture(backgroundTexture);
}

void MainMenu::loadFont() {
    font.loadFromFile("images/fonts/BebasNeue-Regular.ttf");
}

void MainMenu::loadTitle() {
    title = sf::Text("BOMBERMAN", font);
    textProperties::setProperties(title, 170, 170, 20);
    title.setOutlineThickness(4);
}

void MainMenu::loadTexts() {
    for(int i = 0; i < 6; i++) {
        buttonsTexts[i] = sf::Text(stringsForButtonsTexts[i], font);
        textProperties::setProperties(buttonsTexts[i], 50, 0, 270 + i * 85);
        textProperties::setLetterSpacing(buttonsTexts[i], 3);
    }
    centerTextInButtons();
}

void MainMenu::centerTextInButtons() {
    buttonsTexts[0].setPosition(288, buttonsTexts[0].getPosition().y);
    buttonsTexts[1].setPosition(306, buttonsTexts[1].getPosition().y);
    buttonsTexts[2].setPosition(262, buttonsTexts[2].getPosition().y);
    buttonsTexts[3].setPosition(288, buttonsTexts[3].getPosition().y);
    buttonsTexts[4].setPosition(352, buttonsTexts[4].getPosition().y);
    buttonsTexts[5].setPosition(426, buttonsTexts[5].getPosition().y);
}

void MainMenu::loadButtons() { 
    for(int i = 0; i < 6; i++) {
        buttons[i].setPosition(i%2 == 0 ? 87 : 200, 273 + i * 85);  
        buttons[i].setSize(sf::Vector2f(i%2 == 0 ? 823 : 597, 60));
    }
}

void MainMenu::setBackgroundTexture() {
    backgroundTexture.loadFromFile("images/UI/main_menu.png");
}

void MainMenu::draw() {
    window->draw(background);
    window->draw(title);
    // for(sf::RectangleShape button : buttons)
    //     window->draw(button);
    for(sf::Text text : buttonsTexts)
        window->draw(text);
}