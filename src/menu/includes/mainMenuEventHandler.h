#pragma once
#include "mainMenuNavigation.h"

class MainMenuEventHandler {
    private:
        sf::Event event;
        MainMenuNavigation* navigation;
        std::string result;

        void handleEvent();
        
    public:
        MainMenuEventHandler(sf::Event &_event, MainMenuNavigation* _navigation);

        ~MainMenuEventHandler();

        std::string getResult();

};