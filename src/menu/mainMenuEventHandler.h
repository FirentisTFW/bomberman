#pragma once
#include "mainMenuNavigation.h"

class MainMenuEventHandler {
    private:
        sf::Event event;
        MainMenuNavigation* navigation;

        void handleEvent();
        
    public:
        MainMenuEventHandler(sf::Event &_event, MainMenuNavigation* _navigation);

        ~MainMenuEventHandler();

};