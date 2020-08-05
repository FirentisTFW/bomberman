#include "mainMenuEventHandler.h"

MainMenuEventHandler::MainMenuEventHandler(sf::Event &_event, MainMenuNavigation* _navigation) {
    event = _event;
    navigation = _navigation;

    handleEvent();
}

MainMenuEventHandler::~MainMenuEventHandler() {}

void MainMenuEventHandler::handleEvent() {
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Up)
            navigation->up();
        else if(event.key.code == sf::Keyboard::Down)
            navigation->down();
        else if(event.key.code == sf::Keyboard::Return)
            navigation->selectOption();
    }
}