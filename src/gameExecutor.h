#pragma once
#include "game.h"
#include "character.h"
#include "mapLoader.h"
#include "gameEventHandler.h"

class GameExecutor {
    private:
        sf::RenderWindow *window;
        Player *player;
        Game *game;

    public:
        GameExecutor(sf::RenderWindow *_window);

        ~GameExecutor();

        void updateGame(sf::Event &event);

        void handleEvent(sf::Event &event);

        void draw();
};
