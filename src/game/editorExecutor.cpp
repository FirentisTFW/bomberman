#include "includes/editorExecutor.h"

EditorExecutor::EditorExecutor(sf::RenderWindow *_window) {
    window = _window;
    levelEditorUI = new LevelEditorUI(window);
    level = new Level(window, levelEditorUI->backgroundsTexturesFullSize[0], levelEditorUI->getTextureForAsset("box_0"));
}

EditorExecutor::~EditorExecutor() {}

void EditorExecutor::handleEvent(sf::Event &event) {
    LevelEditorEventChecker eventChecker(event, levelEditorUI, level);
    eventChecker.checkEvent(*window);
}

void EditorExecutor::draw() {
    auto mousePos = sf::Mouse::getPosition(*window);
    auto translatedPos = window->mapPixelToCoords(mousePos);

    levelEditorUI->draw();
    level->draw();
    MapHighlight mapHighlight = MapHighlight(translatedPos, level->chosenAssetTexture);
    window->draw(mapHighlight.sprite);
}