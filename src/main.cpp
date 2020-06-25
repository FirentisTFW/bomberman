#include <SFML/Graphics.hpp>
#include "game.h"
#include "character.h"

int main() {

    sf::VideoMode vm(800, 800);									// create window
	sf::RenderWindow window(vm, "Bomberman");
    
    sf::Clock clock;

    window.setFramerateLimit(60);

    srand(time(NULL));                                          // for RNG

    Player *player = new Player(1);

    Game *game = new Game(&window, player);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

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
                        game->characters[0]->shouldCharacterMove('u', game->gameBoard);
                    }
                    else if(event.key.code == sf::Keyboard::Down) {                     // move down
                        game->characters[0]->shouldCharacterMove('d', game->gameBoard);
                    }
                    else if(event.key.code == sf::Keyboard::Left) {                     // move left
                        game->characters[0]->shouldCharacterMove('l', game->gameBoard);
                    }
                    else if(event.key.code == sf::Keyboard::Right) {                    // move right
                        game->characters[0]->shouldCharacterMove('r', game->gameBoard);
                    } // Character movement

                    else if(event.key.code == sf::Keyboard::Space) {
                        game->characters[0]->placeBomb(game->bombs, game->gameBoard);
                        std::cout << "bomb!" << std::endl;
                    }
                }
            }
        }


        if (!game->isGamePaused) {                          // game wasn't paused


            game->updateGameTime();
            game->updateGameBoard();
            Bomb::checkBombsTimers(game->bombs, game->explosions, game->gameBoard);
            Explosion::checkForInactiveExplosions(game->explosions);
            if (event.type != sf::Event::KeyPressed)        // if player pressed a key during this frame, the framerate was already updated, don't do it again
                game->updateCharacterMovementFramerate();
        }

        sf::Time time = clock.getElapsedTime();
		clock.restart().asSeconds();

        window.clear();
        game->draw();
        window.display();
    }

    return 0;
}


    // sf::VideoMode vm(800, 800);									//Tworzenie objektu videomode - tworzenie ekranu
	// sf::RenderWindow window(vm, "Bomberman");

    // window.setFramerateLimit(60);

    //sf::CircleShape shape(100.f);

    //Character* player_1 = new Character();

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     sf::Time time = clock.getElapsedTime();
	// 	clock.restart().asSeconds();

    //     window.clear();
    //     //window.draw(shape);
    //     game->draw();
    //     window.display();