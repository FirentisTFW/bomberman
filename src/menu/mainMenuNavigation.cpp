#include "includes/mainMenuNavigation.h"

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

std::string MainMenuNavigation::getSelectedOption() {
    switch(selectedOption) {
        case(0):
            return "game";
        case(1):
            return "load";
        case(2):
            return "editor";
        case(3):
            return "highscores";
        case(4):
            return "credits";
        case(5):
            return "exit";
        default:
            return "";
    }
}

void MainMenuNavigation::drawSelection() {
    window->draw(buttonsTexts[selectedOption]);
}