#include <SFML/Graphics.hpp>
// #include "menu/mainMenu.h"
// #include "menu/mainMenuNavigation.h"
// #include "menu/mainMenuEventHandler.h"
#include "editor/includes/levelEditorEventChecker.h"
#include "game/includes/mainMenuExecutor.h"
#include "game/includes/gameExecutor.h"
#include "game/includes/editorExecutor.h"

void handleMenuResult(const std::string result, sf::RenderWindow &window, GameExecutor* &gameExecutor, EditorExecutor* &editorExecutor) {
    if(result == "game")
        gameExecutor = new GameExecutor(&window);
    else if(result == "editor")
        editorExecutor = new EditorExecutor(&window);
    else if(result == "exit")
        window.close();
}

int main() {

    sf::VideoMode vm(1000, 800);									// create window
	sf::RenderWindow window(vm, "Bomberman");

    sf::Clock clock;

    window.setFramerateLimit(60);

    srand(time(NULL));                                          // for RNG

    std::string currentScreen = "menu";

    MainMenu mainMenu = MainMenu(&window);
    MainMenuNavigation menuNavigation = MainMenuNavigation(&window, mainMenu.getButtonsTexts());

    GameExecutor *gameExecutor;
    EditorExecutor *editorExecutor;
    MainMenuExecutor *menuExecutor = new MainMenuExecutor(&window);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if(currentScreen == "menu") {
                std::string menuEventResult = menuExecutor->handleEvent(event);
                if (menuEventResult != "") {
                    menuExecutor->handleMenuResult(menuEventResult, gameExecutor, editorExecutor);
                    currentScreen = menuEventResult;
                }
            }
            else if(currentScreen == "editor")
                editorExecutor->handleEvent(event);
            else if(currentScreen == "game") {
                gameExecutor->handleEvent(event);
            }
        }

        // -------------------------------------------------------------------------------------

        sf::Time time = clock.getElapsedTime();
        clock.restart().asSeconds();

        if (currentScreen == "game")
            gameExecutor->updateGame(event);

        // -------------------------------------------------------------------------------------

        window.clear();
        if(currentScreen == "menu")
            menuExecutor->draw();
        else if (currentScreen == "editor")
            editorExecutor->draw();
        else if (currentScreen == "game")
            gameExecutor->draw();

        window.display();
    }

    return 0;
}