#include "mainMenuNavigation.h"

MainMenuNavigation::MainMenuNavigation(sf::RenderWindow *_window, std::array<sf::Text, 6> _buttonsTexts) {
    window = _window;
    buttonsTexts = _buttonsTexts;
    setSelectionColor();
}

MainMenuNavigation::~MainMenuNavigation() {}

void MainMenuNavigation::setSelectionColor() {
    for(int i = 0; i < buttonsTexts.size(); i++) {
        buttonsTexts[i].setFillColor(sf::Color::Yellow);
    }
}

void MainMenuNavigation::up() {
    if (selectionStillInRange(selectedOption-1))
        selectedOption--;
    else
        selectedOption = buttonsTexts.size()-1;
}

void MainMenuNavigation::down() {
    if (selectionStillInRange(selectedOption + 1))
        selectedOption++;
    else
        selectedOption = 0;
}

bool MainMenuNavigation::selectionStillInRange(const int selectionNumber) {
    return selectionNumber >= 0 && selectionNumber < buttonsTexts.size();
}

void MainMenuNavigation::selectOption() {
    switch(selectedOption) {
        case(0):
            break;
        case(1):
            break;
        case(2):
            break;
        case(3):
            break;
        case(4):
            break;
        case(5):
            break;
        default:
            break;
    }
    std::cout << "Selected option: " << selectedOption << std::endl;
}

void MainMenuNavigation::drawSelection() {
    window->draw(buttonsTexts[selectedOption]);
}