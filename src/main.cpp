#include <SFML/Graphics.hpp>
#include "game.h"
#include "character.h"
#include "mapLoader.h"
#include "levelEditorUI.h"
#include "levelEditorClickEvent.h"
#include "editorMapHighlight.h"

int main() {

    sf::VideoMode vm(1000, 800);									// create window
	sf::RenderWindow window(vm, "Bomberman");
    
    sf::Clock clock;

    window.setFramerateLimit(60);

    srand(time(NULL));                                          // for RNG

    LevelEditorUI* levelEditorUI = new LevelEditorUI(&window);

    Level* level = new Level(&window);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                auto mousePos = sf::Mouse::getPosition(window);
                auto translatedPos = window.mapPixelToCoords(mousePos);

                if (levelEditorUI->exitButton.getGlobalBounds().contains(translatedPos))
                    window.close();
                else {
                    LevelEditorClickEvent eventCheck = LevelEditorClickEvent(event, levelEditorUI);
                    std::string clickResult = eventCheck.checkMouseClick(translatedPos);
                    if(clickResult != "0") {
                        if(clickResult != "map")
                            level->assetWasChosen(clickResult);
                        else {
                            sf::Texture &textureForAsset = levelEditorUI->getTextureForAsset(level->chosenAsset);
                            std::cout << "Put " << level->chosenAsset << " on the map!" << std::endl;
                            level->putAssetOnMap(translatedPos, textureForAsset);
                        }
                    }
                }
            }
        }

        auto mouse_pos = sf::Mouse::getPosition(window);
        auto translated_pos = window.mapPixelToCoords(mouse_pos);

        MapHighlight mapHighlight = MapHighlight(translated_pos);

        sf::Time time = clock.getElapsedTime();
        clock.restart().asSeconds();

        window.clear();
        levelEditorUI->draw();
        level->draw();
        window.draw(mapHighlight.rect);
        window.display();
    }

    return 0;
}