#include "levelEditorEventChecker.h"

LevelEditorEventChecker::LevelEditorEventChecker(sf::Event &_event, LevelEditorUI *&_ui, Level *&_level) {
    event = _event;
    ui = _ui;
    level = _level;
}

LevelEditorEventChecker::~LevelEditorEventChecker() {}

void LevelEditorEventChecker::checkEvent(sf::RenderWindow &window) {
    auto mousePos = calculateMousePosition(window);
    
    if(didPlayerCloseWindow(mousePos))
        window.close();
    else if (event.type == sf::Event::MouseButtonPressed) {

        LevelEditorClickEvent eventCheck = LevelEditorClickEvent(event, ui, level);

        if (event.mouseButton.button == sf::Mouse::Left)
            leftMouseButtonPressed(eventCheck, mousePos);
        else if (event.mouseButton.button == sf::Mouse::Right)
            rightMouseButtonPressed(eventCheck, mousePos);
    }
}

sf::Vector2<float> LevelEditorEventChecker::calculateMousePosition(sf::RenderWindow &window) {
    auto mousePos = sf::Mouse::getPosition(window);
    auto translatedPos = window.mapPixelToCoords(mousePos);
}

bool LevelEditorEventChecker::didPlayerCloseWindow(const sf::Vector2<float> &mousePos) {
    return event.type == sf::Event::Closed || (ui->exitButton.getGlobalBounds().contains(mousePos) && event.mouseButton.button == sf::Mouse::Left);
}

void LevelEditorEventChecker::leftMouseButtonPressed(LevelEditorClickEvent &eventCheck, const sf::Vector2<float> &mousePos) {
    std::string clickResult = eventCheck.checkMouseClick(mousePos);
    if (clickResult != "0") {
        if(clickResult.find("background") != std::string::npos)
            clickOnBackground(clickResult);
        else if (clickResult == "map")
            clickOnMap(clickResult, mousePos);
        else
            clickOnAsset(clickResult);
    }
}

void LevelEditorEventChecker::rightMouseButtonPressed(LevelEditorClickEvent &eventCheck, const sf::Vector2<float> &mousePos) {
    if (eventCheck.isClickOnMap())
        level->makeFieldEmpty(mousePos.x / 50, mousePos.y / 50);
}

void LevelEditorEventChecker::clickOnBackground(const std::string clickResult) {
    sf::Texture &textureForBackground = ui->getTextureForAsset(clickResult);
    level->setBackground(textureForBackground, int(clickResult[11]) - 48);
}

void LevelEditorEventChecker::clickOnAsset(const std::string clickResult) {
    level->assetWasChosen(clickResult);
    level->chosenAssetTexture = ui->getTextureForAsset(level->chosenAsset);
}

void LevelEditorEventChecker::clickOnMap(const std::string clickResult, const sf::Vector2<float> &mousePos) {
    sf::Texture &textureForAsset = ui->getTextureForAsset(level->chosenAsset);
    level->putAssetOnMap(mousePos, textureForAsset);
    std::cout << "Put " << level->chosenAsset << " on the map!" << std::endl;
}