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

    Level* level = new Level(&window, levelEditorUI->backgroundsTexturesFullSize[0]);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = sf::Mouse::getPosition(window);
                auto translatedPos = window.mapPixelToCoords(mousePos);

                LevelEditorClickEvent eventCheck = LevelEditorClickEvent(event, levelEditorUI, level);

                if(event.mouseButton.button == sf::Mouse::Left) {
                    if (levelEditorUI->exitButton.getGlobalBounds().contains(translatedPos))
                        window.close();
                    else {
                        std::string clickResult = eventCheck.checkMouseClick(translatedPos);
                        if (clickResult != "0") {
                            if(clickResult.find("background") != std::string::npos) {
                                sf::Texture &textureForBackground = levelEditorUI->getTextureForAsset(clickResult);
                                level->setBackground(textureForBackground, int(clickResult[11]) - 48);
                            }
                            else if (clickResult != "map")
                                level->assetWasChosen(clickResult);
                            else {
                                sf::Texture &textureForAsset = levelEditorUI->getTextureForAsset(level->chosenAsset);
                                level->putAssetOnMap(translatedPos, textureForAsset);
                                std::cout << "Put " << level->chosenAsset << " on the map!" << std::endl;
                            }
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    if(eventCheck.isClickOnMap())
                        level->makeFieldEmpty(translatedPos.x/50, translatedPos.y/50);
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