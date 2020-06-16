#include <SFML/Graphics.hpp>
#include "game.h"
#include "player.h"

int main() {

    sf::VideoMode vm(800, 800);									// create window
	sf::RenderWindow window(vm, "Bomberman");
    
    sf::Clock clock;

    window.setFramerateLimit(60);

    Game *game = new Game(&window);

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
                    game->players[0]->speed++;                      // TEST - speed testing
                    game->updateGameBoard();
                }

                // Player movement
                else if(!game->isGamePaused) {
                    if(event.key.code == sf::Keyboard::Up) {                            // move up
                        game->players[0]->shouldPlayerMove('u');
                    }
                    else if(event.key.code == sf::Keyboard::Down) {                     // move down
                        game->players[0]->shouldPlayerMove('d');
                    }
                    else if(event.key.code == sf::Keyboard::Left) {                     // move left
                        game->players[0]->shouldPlayerMove('l');
                    }
                    else if(event.key.code == sf::Keyboard::Right) {                    // move right
                        game->players[0]->shouldPlayerMove('r');
                    } // Player movement

                    else if(event.key.code == sf::Keyboard::Space) {
                        std::cout << "bomb!" << std::endl;
                    }
                }
            }
        }


        if (!game->isGamePaused) {                          // game wasn't paused
            
            game->updateGameTime();
            if (event.type != sf::Event::KeyPressed)        // if player pressed a key during this frame, the framerate was already updated, don't do it again
                game->updatePlayerMovementFramerate();
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

    //Player* player_1 = new Player();

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