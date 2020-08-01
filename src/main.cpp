#include <SFML/Graphics.hpp>
#include "game.h"
#include "character.h"
#include "mapLoader.h"
#include "editor/levelEditorEventChecker.h"

int main() {

    sf::VideoMode vm(1000, 800);									// create window
	sf::RenderWindow window(vm, "Bomberman");
    
    sf::Clock clock;

    window.setFramerateLimit(60);

    srand(time(NULL));                                          // for RNG

    LevelEditorUI* levelEditorUI = new LevelEditorUI(&window);

    sf::Texture &startingAssetTexture = levelEditorUI->getTextureForAsset("box_0");
    Level *level = new Level(&window, levelEditorUI->backgroundsTexturesFullSize[0], startingAssetTexture);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            LevelEditorEventChecker eventChecker(event, levelEditorUI, level);
            eventChecker.checkEvent(window);
        }

        auto mousePos = sf::Mouse::getPosition(window);
        auto translatedPos = window.mapPixelToCoords(mousePos);

        MapHighlight mapHighlight = MapHighlight(translatedPos, level->chosenAssetTexture);

        sf::Time time = clock.getElapsedTime();
        clock.restart().asSeconds();

        window.clear();
        levelEditorUI->draw();
        level->draw();
        window.draw(mapHighlight.sprite);
        window.display();
    }

    return 0;
}