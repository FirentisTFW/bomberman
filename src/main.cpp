#include <SFML/Graphics.hpp>
#include "menu/mainMenu.h"
#include "menu/mainMenuNavigation.h"
#include "menu/mainMenuEventHandler.h"
#include "game.h"
#include "character.h"
#include "mapLoader.h"
#include "editor/levelEditorEventChecker.h"

void handleMenuResult(const std::string result, sf::RenderWindow &window, LevelEditorUI* &levelEditorUI, Level* &level) {
    if(result == "new") {
        
    }
    else if(result == "editor") {
        levelEditorUI = new LevelEditorUI(&window);
        level = new Level(&window, levelEditorUI->backgroundsTexturesFullSize[0], levelEditorUI->getTextureForAsset("box_0"));
    }
    else if(result == "exit") {
        // window.close();
    }
}

int main() {

    sf::VideoMode vm(1000, 800);									// create window
	sf::RenderWindow window(vm, "Bomberman");
    
    sf::Clock clock;

    window.setFramerateLimit(60);

    srand(time(NULL));                                          // for RNG

    std::string currentScreen = "menu";

    // LevelEditorUI *levelEditorUI = new LevelEditorUI(&window);

    LevelEditorUI *levelEditorUI;

    // sf::Texture &startingAssetTexture = levelEditorUI->getTextureForAsset("box_0");
    // Level *level = new Level(&window, levelEditorUI->backgroundsTexturesFullSize[0], startingAssetTexture);

    Level *level;

    MainMenu mainMenu = MainMenu(&window);
    MainMenuNavigation menuNavigation = MainMenuNavigation(&window, mainMenu.getButtonsTexts());

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            MainMenuEventHandler eventHandler = MainMenuEventHandler(event, &menuNavigation);
            std::string menuEventResult = eventHandler.getResult();
            handleMenuResult(menuEventResult, window, levelEditorUI, level);
            if (menuEventResult != "")
                currentScreen = menuEventResult;
        }

        auto mousePos = sf::Mouse::getPosition(window);
        auto translatedPos = window.mapPixelToCoords(mousePos);

        sf::Time time = clock.getElapsedTime();
        clock.restart().asSeconds();

        window.clear();
        if(currentScreen == "menu") {
            mainMenu.draw();
            menuNavigation.drawSelection();
        }
        else if (currentScreen == "editor") {
            levelEditorUI->draw();
            level->draw();
            MapHighlight mapHighlight = MapHighlight(translatedPos, level->chosenAssetTexture);
            window.draw(mapHighlight.sprite);
        }
        window.display();
    }

    return 0;
}