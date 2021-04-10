#pragma once
#include "game.h"
#include "character.h"

class GameEventHandler {
    private:
        sf::Event event;
        Game *game;

        sf::Vector2<float> calculateMousePosition(sf::RenderWindow &window);

        bool didPlayerCloseWindow(const sf::Vector2<float> &mousePos);

        void handleMouseClick(const sf::Vector2<float> &mousePos);

        void handlePressedKey();

    public:
        GameEventHandler(sf::Event &_event, Game* &_game);

        ~GameEventHandler();

        void handleEvent(sf::RenderWindow &window);
};