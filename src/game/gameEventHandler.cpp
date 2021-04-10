#include "includes/gameEventHandler.h"

GameEventHandler::GameEventHandler(sf::Event &_event, Game *&_game) {
    event = _event;
    game = _game;
}

GameEventHandler::~GameEventHandler() {}

void GameEventHandler::handleEvent(sf::RenderWindow &window) {
    auto mousePos = calculateMousePosition(window);

    if (didPlayerCloseWindow(mousePos))
        window.close();
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        handleMouseClick(mousePos);
    if (event.type == sf::Event::KeyPressed)
        handlePressedKey();
}


sf::Vector2<float> GameEventHandler::calculateMousePosition(sf::RenderWindow &window) {
    auto mousePos = sf::Mouse::getPosition(window);
    auto translatedPos = window.mapPixelToCoords(mousePos);
}

bool GameEventHandler::didPlayerCloseWindow(const sf::Vector2<float> &mousePos) {
    return event.type == sf::Event::Closed || (game->gameUI->exitButton.getGlobalBounds().contains(mousePos) && event.mouseButton.button == sf::Mouse::Left);
}

void GameEventHandler::handleMouseClick(const sf::Vector2<float> &mousePos) {
    if (game->gameUI->pauseButton.getGlobalBounds().contains(mousePos))
        game->pauseOrUnpauseGame();
}

void GameEventHandler::handlePressedKey() {         
    if(event.key.code == sf::Keyboard::Escape)        // ESC pause the game
        game->pauseOrUnpauseGame();

    // Character movement
    else if(!game->isGamePaused) {
        if(event.key.code == sf::Keyboard::Up)                            // move up
            game->characters[0]->tryToMove('u', game->gameBoard, game->bombs);
        else if(event.key.code == sf::Keyboard::Down)                     // move down
            game->characters[0]->tryToMove('d', game->gameBoard, game->bombs);
        else if(event.key.code == sf::Keyboard::Left)                     // move left
            game->characters[0]->tryToMove('l', game->gameBoard, game->bombs);
        else if(event.key.code == sf::Keyboard::Right)                    // move right
            game->characters[0]->tryToMove('r', game->gameBoard, game->bombs);
        else if(event.key.code == sf::Keyboard::Space)
            game->characters[0]->tryToPlaceBomb(game->bombs, game->gameBoard, game->diggedBombs, game->specialWeapons, game->gameTextures->bombTexture, game->gameTextures->specialWeaponsTextures);
    }
}