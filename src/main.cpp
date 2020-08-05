#include <SFML/Graphics.hpp>
#include "menu/mainMenu.h"
#include "menu/mainMenuNavigation.h"
#include "menu/mainMenuEventHandler.h"
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

    MainMenu mainMenu = MainMenu(&window);
    MainMenuNavigation menuNavigation = MainMenuNavigation(&window, mainMenu.getButtonsTexts());

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            MainMenuEventHandler eventHandler = MainMenuEventHandler(event, &menuNavigation);
        }

        // auto mousePos = sf::Mouse::getPosition(window);
        // auto translatedPos = window.mapPixelToCoords(mousePos);

        // MapHighlight mapHighlight = MapHighlight(translatedPos, level->chosenAssetTexture);

        sf::Time time = clock.getElapsedTime();
        clock.restart().asSeconds();

        window.clear();
        // levelEditorUI->draw();
        // level->draw();
        // window.draw(mapHighlight.sprite);
        mainMenu.draw();
        menuNavigation.drawSelection();
        window.display();
    }

    return 0;
}