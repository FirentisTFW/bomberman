#include "gameExecutor.h"

GameExecutor::GameExecutor(sf::RenderWindow *_window) {
    window = _window;
    player = new Player('b');
    gameTextures = new GameTextures();
    gameUI = new GameUI(player->lives, player->color);
    game = new Game(_window, player, gameTextures, gameUI);
    MapLoader mapLoader;
    mapLoader.loadMap(game->boxes, game->characters, gameTextures->boxesTextures, gameTextures->charactersTextures, gameTextures->backgroundTexture);
    game->loadBackground();

    // TODO: character selection
    game->characters[0]->isHuman = true;
}

GameExecutor::~GameExecutor() {}

void GameExecutor::handleEvent(sf::Event &event) {
    GameEventHandler gameEventHandler = GameEventHandler(event, game);
    gameEventHandler.handleEvent(*window);
}

void GameExecutor::updateGame(sf::Event &event) {
    if (!game->isGamePaused) {                          // game wasn't paused
        game->updateGameTime();
        game->updateGameBoard();
        game->updateAnimations();
        game->placeAiBombs();
        AiMovement::createCharactersMovement(game->characters, game->gameBoard, game->bombs);
        Bomb::checkBombsTimers(game->bombs, game->explosions, game->gameBoard, gameTextures->explosionTexture);
        Explosion::checkForInactiveExplosions(game->explosions);
        game->updateCharacterMovementFramerate();
    }
}

void GameExecutor::draw() {
    game->draw();
}
