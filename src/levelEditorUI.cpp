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

    loadBackgrounds();

    loadBoxes();

    loadWalls();

    loadCharacters();
}

LevelEditorUI::~LevelEditorUI() {}

void LevelEditorUI::loadTextures() {
    for(int i = 0; i < 5; i++) {
        boxesTextures[i].loadFromFile("images/boxes/box_" + std::to_string(i+1) + ".png");
        boxes[i].setTexture(boxesTextures[i]);
    }
    for(int i = 0; i < 4; i++) {
        wallsTextures[i].loadFromFile("images/boxes/stone_wall_" + std::to_string(i+1) + ".png");
        walls[i].setTexture(wallsTextures[i]);
    }
    for(int i = 0; i < 4; i++) {
        charactersTextures[i].loadFromFile("images/level_editor_icons/characters/character_" + std::to_string(i+1) + ".png");
        characters[i].setTexture(charactersTextures[i]);
    }
    for(int i = 0; i < 2; i++) {
        backgroundsTextures[i].loadFromFile("images/level_editor_icons/backgrounds/background_" + std::to_string(i+1) + ".png");
        backgrounds[i].setTexture(backgroundsTextures[i]);
    }
    for(int i = 0; i < 2; i++)
        backgroundsTexturesFullSize[i].loadFromFile("images/backgrounds/background_" + std::to_string(i+1) + ".png");
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
    textProperties::setProperties(backgroundsText, 30, 830, 10);

    boxesText = sf::Text("Boxes", font);
    textProperties::setProperties(boxesText, 30, 865, 115);

    charactersText = sf::Text("Characters", font);
    textProperties::setProperties(charactersText, 30, 835, 450);

    wallsText = sf::Text("Walls", font);
    textProperties::setProperties(wallsText, 30, 865, 275);
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

void LevelEditorUI::loadBackgrounds() {
    for (int i = 0; i < 2; i++) {
        backgrounds[i].setPosition(813 + i * 62, 55);
    }
}

void LevelEditorUI::loadBoxes() {
    for (int i = 0; i < 5; i++) {
        if (i < 3)
            boxes[i].setPosition(813 + i * 62, 160);
        else
            boxes[i].setPosition(813 + (i-3) * 62, 220);
    }
}

void LevelEditorUI::loadWalls() {
    for (int i = 0; i < 5; i++) {
        if (i < 3)
            walls[i].setPosition(813 + i * 62, 325);
        else
            walls[i].setPosition(813 + (i - 3) * 62, 385);
    }
}

void LevelEditorUI::loadCharacters() {
    characters[0].setPosition(830, 490);
    characters[1].setPosition(920, 490);
    characters[2].setPosition(830, 550);
    characters[3].setPosition(920, 550);
}

sf::Texture& LevelEditorUI::getTextureForAsset(std::string asset) {
    if (asset.find("box") != std::string::npos)
        return boxesTextures[stoi(asset.substr(4))];
    else if (asset.find("wall") != std::string::npos)
        return wallsTextures[stoi(asset.substr(5))];
    else if (asset.find("character") != std::string::npos)
        return charactersTextures[stoi(asset.substr(10))];
    else if (asset.find("background") != std::string::npos)
        return backgroundsTexturesFullSize[stoi(asset.substr(11))];
}

void LevelEditorUI::draw() {
    
    window->draw(sideBar);

    window->draw(backgroundsText);
    window->draw(charactersText);
    window->draw(boxesText);
    window->draw(wallsText);

    window->draw(save);
    window->draw(reset);
    window->draw(exit);

    for(sf::Sprite box : boxes)
        window->draw(box);
    for(sf::Sprite wall : walls)
        window->draw(wall);
    for(sf::Sprite character : characters)
        window->draw(character);
    for(sf::Sprite background : backgrounds)
        window->draw(background);
}