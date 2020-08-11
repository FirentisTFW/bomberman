#include "gameExecutor.h"

GameExecutor::GameExecutor(sf::RenderWindow *_window) {
    window = _window;
    // player = _player;
    // game = _game;
    player = new Player('b');
    game = new Game(_window, player);
    std::cout << game->gameTime[0] << std::endl;
    game->gameUI = new GameUI(player->lives, player->color);
    MapLoader mapLoader;
    mapLoader.loadMap(game->boxes, game->characters, game->boxesTextures, game->charactersTextures, game->backgroundTexture);
    game->loadBackground();
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
        game->updateAnimationsOnBoard();
        Bomb::checkBombsTimers(game->bombs, game->explosions, game->gameBoard, game->explosionTexture);
        Explosion::checkForInactiveExplosions(game->explosions);
        if (event.type != sf::Event::KeyPressed)        // if player pressed a key during this frame, the framerate was already updated, don't do it again
            game->updateCharacterMovementFramerate();
    }
}

void GameExecutor::draw() {
    game->draw();
}
