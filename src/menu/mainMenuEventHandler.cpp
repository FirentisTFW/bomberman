#include "includes/mainMenuEventHandler.h"

MainMenuEventHandler::MainMenuEventHandler(sf::Event &_event, MainMenuNavigation* _navigation) {
    event = _event;
    navigation = _navigation;
    result = "";

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
            result = navigation->getSelectedOption();
    }
}

std::string MainMenuEventHandler::getResult() {
    return result;
}