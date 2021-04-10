#include "includes/mainMenuExecutor.h"

MainMenuExecutor::MainMenuExecutor(sf::RenderWindow *_window) {
    window = _window;
    mainMenu = new MainMenu(window);
    menuNavigation = new MainMenuNavigation(window, mainMenu->getButtonsTexts());
}

MainMenuExecutor::~MainMenuExecutor() {}

std::string MainMenuExecutor::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::Closed)
        window->close();

    MainMenuEventHandler eventHandler = MainMenuEventHandler(event, menuNavigation);
    std::string menuEventResult = eventHandler.getResult();
    return menuEventResult;
}

void MainMenuExecutor::handleMenuResult(const std::string result, GameExecutor *&gameExecutor, EditorExecutor *&editorExecutor) {
    if (result == "game")
        gameExecutor = new GameExecutor(window);
    else if (result == "editor")
        editorExecutor = new EditorExecutor(window);
    else if (result == "exit")
        window->close();
}

void MainMenuExecutor::draw() {
    mainMenu->draw();
    menuNavigation->drawSelection();
}