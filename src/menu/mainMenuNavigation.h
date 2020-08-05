#pragma once
#include "mainMenu.h"

class MainMenuNavigation {
    private:
        sf::RenderWindow *window;
        int selectedOption = 0;
        std::array<sf::Text, 6> buttonsTexts;           // these texts when selected overlap texts from MainMenu creating option selection effect 

        void setSelectionColor();

    public:
        MainMenuNavigation(sf::RenderWindow *_window, std::array<sf::Text, 6> _buttonsTexts);

        ~MainMenuNavigation();

        void up();

        void down();

        bool selectionStillInRange(const int selectionNumber);

        void selectOption();

        void drawSelection();
};