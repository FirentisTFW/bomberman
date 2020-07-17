#include "levelEditorUI.h"

LevelEditorUI::LevelEditorUI(sf::RenderWindow* _window) {

    window = _window;

    sideBarTexture.loadFromFile("images/UI/side_bar_editor.png");
    sideBar.setTexture(sideBarTexture);
    sideBar.setPosition(800, 0);

    loadTextures();

    loadFont();

    loadTexts();

    loadButtons();

}

LevelEditorUI::~LevelEditorUI() {}

void LevelEditorUI::loadTextures() {

    for(int i = 0; i < 5; i++) {
        boxesTextures[i].loadFromFile("images/boxes/box_" + std::to_string(i+1) + ".png");
        boxes[i].setTexture(boxesTextures[i]);
    }
    for(int i = 0; i < 4; i++) {
        boxesTextures[i + 4].loadFromFile("images/boxes/stone_wall_" + std::to_string(i+1) + ".png");
        boxes[i+4].setTexture(boxesTextures[i+4]);
    }
    for(int i = 0; i < 4; i++) {
        charactersTextures[i].loadFromFile("images/characters/character_" + std::to_string(i+1) + ".png");
        characters[i].setTexture(charactersTextures[i]);
    }
    for(int i = 0; i < 2; i++) {
        backgroundsTextures[i].loadFromFile("images/backgrounds/background_" + std::to_string(i+1) + ".png");
        backgrounds[i].setTexture(backgroundsTextures[i]);
    }
}

void LevelEditorUI::loadFont() {
    font.loadFromFile("images/fonts/BebasNeue-Regular.ttf");
}

void LevelEditorUI::loadTexts() {

    save = sf::Text("SAVE", font);
    textProperties::setProperties(save, 40, 868, 615);

    reset = sf::Text("RESET", font);
    textProperties::setProperties(reset, 40, 860, 675);

    exit = sf::Text("EXIT", font);
    textProperties::setProperties(exit, 40, 872, 735);

    backgroundsText = sf::Text("Backgrounds", font);
    textProperties::setProperties(backgroundsText, 30, 830, 15);

    boxesText = sf::Text("Boxes", font);
    textProperties::setProperties(boxesText, 30, 865, 150);

    charactersText = sf::Text("Characters", font);
    textProperties::setProperties(charactersText, 30, 835, 400);
}

void LevelEditorUI::loadButtons() { 

    saveButton.setPosition(807, 616);
    saveButton.setSize(sf::Vector2f(185, 52));
    saveButton.setFillColor(sf::Color::White);

    resetButton.setPosition(807, 675);
    resetButton.setSize(sf::Vector2f(185, 52));
    resetButton.setFillColor(sf::Color::White);

    exitButton.setPosition(807, 736);
    exitButton.setSize(sf::Vector2f(185, 52));
    exitButton.setFillColor(sf::Color::White);
}

void LevelEditorUI::draw() {
    
    window->draw(sideBar);

    window->draw(backgroundsText);
    window->draw(charactersText);
    window->draw(boxesText);

    window->draw(save);
    window->draw(reset);
    window->draw(exit);

    // for(sf::Sprite box : boxes)
    //     window->draw(box);
    // for(sf::Sprite character : characters)
    //     window->draw(character);
    // for(sf::Sprite background : backgrounds)
    //     window->draw(background);
}