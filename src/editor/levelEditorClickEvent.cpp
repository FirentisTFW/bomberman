#include "levelEditorClickEvent.h"

LevelEditorClickEvent::LevelEditorClickEvent(const sf::Event &_event, LevelEditorUI* &_ui, Level* &_level) {
    event = _event;
    ui = _ui;
    level = _level;
}

LevelEditorClickEvent::~LevelEditorClickEvent() {}

std::string LevelEditorClickEvent::checkMouseClick(sf::Vector2f _mousePosition) {

    mousePosition = _mousePosition;

    if(!checkClickOnButtons()) {
        std::string clickResult = checkClickOnAssets();
        if(clickResult == "0") {
            if(!isClickOnMap())
                return "0";
            else
                return "map";
        }
        else
            return clickResult;
    }
    return "0";

}

bool LevelEditorClickEvent::checkClickOnButtons() {

    if (ui->saveButton.getGlobalBounds().contains(mousePosition)) {
        std::cout << "save level" << std::endl;
        LevelSaver saver;
        saver.saveLevel(level->backgroundTextureId, level->boxes, level->characters);
        return true;
    }
    else if (ui->resetButton.getGlobalBounds().contains(mousePosition)) {
        std::cout << "reset level" << std::endl;
        level->resetLevel();
        return true;
    }

    return false;
}

std::string LevelEditorClickEvent::checkClickOnAssets() {
    for (int i = 0; i < 4; i++)
        if (ui->boxes[i].getGlobalBounds().contains(mousePosition))
            return "box_" + std::to_string(i);
    for (int i = 0; i < 4; i++)
        if (ui->walls[i].getGlobalBounds().contains(mousePosition)) 
            return "wall_" + std::to_string(i);
    for (int i = 0; i < 4; i++)
        if (ui->characters[i].getGlobalBounds().contains(mousePosition))
            return "character_" + std::to_string(i);
    for (int i = 0; i < 4; i++)
        if (ui->backgrounds[i].getGlobalBounds().contains(mousePosition)) 
            return "background_" + std::to_string(i);
    return "0";
}

bool LevelEditorClickEvent::isClickOnMap() {
    return mousePosition.x > -1 && mousePosition.x < 800 && mousePosition.y > -1 && mousePosition.y < 800;
}