#include <SFML/Graphics.hpp>
#include "game.h"
#include "character.h"
#include "mapLoader.h"
#include "levelEditorUI.h"

int main() {

    sf::VideoMode vm(1000, 800);									// create window
	sf::RenderWindow window(vm, "Bomberman");
    
    sf::Clock clock;

    window.setFramerateLimit(60);

    srand(time(NULL));                                          // for RNG

    LevelEditorUI *levelEditorUI = new LevelEditorUI(&window);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            // MOUSE BUTTONS
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                auto mouse_pos = sf::Mouse::getPosition(window);
                auto translated_pos = window.mapPixelToCoords(mouse_pos);

                if (levelEditorUI->saveButton.getGlobalBounds().contains(translated_pos)) {
                    std::cout << "save level" << std::endl;
                } // ~ MOUSE BUTTONS
                else if (levelEditorUI->resetButton.getGlobalBounds().contains(translated_pos)) {
                    std::cout << "reset level" << std::endl;
                } // ~ MOUSE BUTTONS
                else if (levelEditorUI->exitButton.getGlobalBounds().contains(translated_pos))
                    window.close();
            } // ~ MOUSE BUTTONS

            // KEYBOARD KEYS
            if (event.type == sf::Event::KeyPressed) {          

            } // ~ KEYBOARD KEYS
        }

        sf::Time time = clock.getElapsedTime();
		clock.restart().asSeconds();

        window.clear();
        levelEditorUI->draw();
        window.display();

    }

    return 0;
}