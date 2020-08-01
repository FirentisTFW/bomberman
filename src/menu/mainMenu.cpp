#include "mainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* _window) {
    window = _window;

    // setBackground();
    loadFont();
    loadButtons();
    loadTexts();
}

MainMenu::~MainMenu() {}

void MainMenu::setBackground(sf::Texture &_background) {
    background.setPosition(0, 0);
    background.setTexture(_background);
}

void MainMenu::loadFont() {
    font.loadFromFile("images/fonts/BebasNeue-Regular.ttf");
}

void MainMenu::loadTexts() {

}

void MainMenu::loadButtons() { 
    for(int i = 0; i < 6; i++) {
        buttons[i].setPosition(i%2 == 0 ? 87 : 200, 273 + i * 86);  
        buttons[i].setSize(sf::Vector2f(i%2 == 0 ? 823 : 597, 60));
    }
}

void MainMenu::draw() {
    window->draw(background);
    for(sf::RectangleShape button : buttons)
        window->draw(button);
}