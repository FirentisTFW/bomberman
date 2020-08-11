#pragma once
#include "menu/mainMenu.h"
#include "menu/mainMenuNavigation.h"
#include "menu/mainMenuEventHandler.h"
#include "gameExecutor.h"
#include "editorExecutor.h"

class MainMenuExecutor {
    private:
        sf::RenderWindow *window;
        MainMenu *mainMenu;
        MainMenuNavigation *menuNavigation;

    public:
        MainMenuExecutor(sf::RenderWindow *_window);

        ~MainMenuExecutor();

        std::string handleEvent(sf::Event &event);

        void handleMenuResult(const std::string result, GameExecutor* &gameExecutor, EditorExecutor* &editorExecutor);

        void draw();
};