#pragma once
#include "mainMenu.h"

class MainMenuNavigation {
    private:
        sf::RenderWindow *window;
        int selectedOption = 0;
        std::array<sf::Text, 6> buttonsTexts;           // these texts when selected overlap texts from MainMenu creating option selection effect 

        void setSelectionColor();

        bool selectionStillInRange(const int selectionNumber);

    public:
        MainMenuNavigation(sf::RenderWindow *_window, std::array<sf::Text, 6> _buttonsTexts);

        ~MainMenuNavigation();

        void up();

        void down();

        std::string getSelectedOption();

        void drawSelection();
};