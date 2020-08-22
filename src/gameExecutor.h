#pragma once
#include "game.h"
#include "gameTextures.h"
#include "character.h"
#include "mapLoader.h"
#include "gameEventHandler.h"
#include "aiMovement.h"

class GameExecutor {
    private:
        sf::RenderWindow *window;
        Player *player;
        Game *game;
        GameTextures* gameTextures;
        GameUI* gameUI;

    public:
        GameExecutor(sf::RenderWindow *_window);

        ~GameExecutor();

        void updateGame(sf::Event &event);

        void handleEvent(sf::Event &event);

        void draw();
};
