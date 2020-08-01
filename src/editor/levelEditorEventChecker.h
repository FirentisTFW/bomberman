#pragma once
#include "levelEditorUI.h"
#include "levelEditorClickEvent.h"
#include "editorMapHighlight.h"

class LevelEditorEventChecker {
    private:
        sf::Event event;
        LevelEditorUI *ui;
        Level *level;

        bool didPlayerCloseWindow(const sf::Vector2<float> &mousePos);

        sf::Vector2<float> calculateMousePosition(sf::RenderWindow &window);

        void leftMouseButtonPressed(LevelEditorClickEvent &eventCheck, const sf::Vector2<float> &mousePos);

        void rightMouseButtonPressed(LevelEditorClickEvent &eventCheck, const sf::Vector2<float> &mousePos);

        void clickOnBackground(const std::string clickResult);

        void clickOnAsset(const std::string clickResult);

        void clickOnMap(const std::string clickResult, const sf::Vector2<float> &mousePos);

    public:
        LevelEditorEventChecker(sf::Event &_event, LevelEditorUI *&_ui, Level *&_level);

        ~LevelEditorEventChecker();

        void checkEvent(sf::RenderWindow &window);

};