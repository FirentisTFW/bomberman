#include "gameExecutor.h"

GameExecutor::GameExecutor(sf::RenderWindow *_window) {
    window = _window;
    // player = _player;
    // game = _game;
    player = new Player('b');
    game = new Game(_window, player);
    std::cout << game->gameTime[0] << std::endl;
    game->gameUI = new GameUI(player->lives, player->color);
    mapLoader::loadMap(game->boxes, game->characters, game->boxesTextures, game->charactersTextures);
}

GameExecutor::~GameExecutor() {}

void GameExecutor::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::Closed)
        window->close();

    // MOUSE BUTTONS
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        auto mouse_pos = sf::Mouse::getPosition(*window);
        auto translated_pos = window->mapPixelToCoords(mouse_pos);

        // check which button was clicked
        if (game->gameUI->pauseRect.getGlobalBounds().contains(translated_pos)) {
            if(!game->isGamePaused)
                game->isGamePaused = true;
            else
                game->isGamePaused = false;
            std::cout << "Game paused/unpaused" << std::endl;
        }
        else if (game->gameUI->exitRect.getGlobalBounds().contains(translated_pos)) {
            std::cout << "EXIT" << std::endl;
            window->close();
        }
    }   // ~ MOUSE BUTTONS

    
    // KEYBOARD KEYS
    if (event.type == sf::Event::KeyPressed) {          
        if(event.key.code == sf::Keyboard::Escape) {        // ESC pause the game
            // if(!game->isGamePaused)
            //     game->isGamePaused = true;
            // else
            //     game->isGamePaused = false;
            // std::cout << "Game paused" << std::endl;
            game->characters[0]->speed++;                      // TEST - speed testing
            game->showGameBoard();
        }

        // Character movement
        else if(!game->isGamePaused) {
            if(event.key.code == sf::Keyboard::Up) {                            // move up
                game->characters[0]->shouldCharacterMove('u', game->gameBoard, game->bombs);
            }
            else if(event.key.code == sf::Keyboard::Down) {                     // move down
                game->characters[0]->shouldCharacterMove('d', game->gameBoard, game->bombs);
            }
            else if(event.key.code == sf::Keyboard::Left) {                     // move left
                game->characters[0]->shouldCharacterMove('l', game->gameBoard, game->bombs);
            }
            else if(event.key.code == sf::Keyboard::Right) {                    // move right
                game->characters[0]->shouldCharacterMove('r', game->gameBoard, game->bombs);
            } // Character movement

            else if(event.key.code == sf::Keyboard::Space) {
                game->characters[0]->placeBomb(game->bombs, game->gameBoard, game->diggedBombs, game->specialWeapons, game->bombTexture, game->specialWeaponsTextures);
            }
        }
    } // ~ KEYBOARD KEYS
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

    // sf::Time time = clock.getElapsedTime();
    // clock.restart().asSeconds();
}

void GameExecutor::draw() {
    game->draw();
}
