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
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {          
                if(event.key.code == sf::Keyboard::Escape) {        // ESC pause the game
                    if(!game->isGamePaused)
                        game->isGamePaused = true;
                    else
                        game->isGamePaused = false;
                    std::cout << "ESC" << std::endl;
                }

                // Player movement
                else if(event.key.code == sf::Keyboard::Up) {                       // move up
                    // game->players[0]->rect.move(0, -game->players[0]->speed);
                    game->players[0]->move('u');
                }
                else if(event.key.code == sf::Keyboard::Down) {                     // move down
                    // game->players[0]->rect.move(0, game->players[0]->speed);
                    game->players[0]->move('d');
                }
                else if(event.key.code == sf::Keyboard::Left) {                     // move left
                    // game->players[0]->rect.move(-game->players[0]->speed, 0);
                    game->players[0]->move('l');
                }
                else if(event.key.code == sf::Keyboard::Right) {                    // move right
                    // game->players[0]->rect.move(game->players[0]->speed, 0);
                    game->players[0]->move('r');
                } // Player movement

                else if(event.key.code == sf::Keyboard::Space) {
                    std::cout << "bomb!" << std::endl;
                }
            }

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