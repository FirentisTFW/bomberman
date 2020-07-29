#include "level.h"

Level::Level(sf::RenderWindow* _window, sf::Texture &_background, sf::Texture &_chosenAssetTexture) {
    clearGameBoard();
    setBackground(_background, 0);
    chosenAsset = "box_0";
    chosenAssetTexture = _chosenAssetTexture;
    window = _window;
}

Level::~Level() {}

void Level::clearGameBoard() {
    for (int i = 0; i < 16; i++) {                      
        for (int j = 0; j < 16; j++) {
            gameBoard[i][j] = "0";
        }
    }
}

void Level::resetLevel() {
    clearGameBoard();
    boxes.clear();
    characters.clear();
}

void Level::setBackground(sf::Texture &_background, int _textureId) {
    background.setPosition(0, 0);
    background.setTexture(_background);
    backgroundTextureId = _textureId;
}

void Level::assetWasChosen(std::string assetName) {
    chosenAsset = assetName;
}

void Level::putAssetOnMap(sf::Vector2f mousePosition, sf::Texture &texture) {
    int posX = mousePosition.x / 50;
    int posY = mousePosition.y / 50;

    makeFieldEmpty(posX, posY);

    if (chosenAsset.find("box") != std::string::npos)
        putBoxOnMap(true, posX, posY, texture);
    else if (chosenAsset.find("wall") != std::string::npos)
        putBoxOnMap(false, posX, posY, texture);
    else if (chosenAsset.find("character") != std::string::npos)
        putCharacterOnMap(posX, posY, texture);
}

void Level::makeFieldEmpty(const int posX, const int posY) {
    if (gameBoard[posY][posX] != "0")
        checkWhatAssetIsOnPosition(posX, posY);
    gameBoard[posY][posX] = "0";
}

void Level::removeCharacterFromMap(char _color) {
    for(int i = 0; i < characters.size(); i++)
        if (characters[i]->color == _color)
            makeFieldEmpty(characters[i]->posX, characters[i]->posY);
}

void Level::checkWhatAssetIsOnPosition(const int posX,const  int posY) {
    std::string currentAssetOnPosition = gameBoard[posY][posX];
    if (currentAssetOnPosition == "box" || currentAssetOnPosition == "wall")
        removeBoxFromPosition(posX, posY);
    else if (currentAssetOnPosition == "character")
        removeCharacterFromPosition(posX, posY);
}

void Level::removeBoxFromPosition(const int _posX, const int _posY) {
    int boxesSize = boxes.size();
    for(int i = 0; i < boxesSize; i++) {
        if (boxes[i]->posX == _posX && boxes[i]->posY == _posY) {
            boxes.erase(boxes.begin() + i);
            break;
        }
    }
}

void Level::removeCharacterFromPosition(const int _posX, const int _posY) {
    for(int i = 0; i < characters.size(); i++) {
        if (characters[i]->posX == _posX && characters[i]->posY == _posY) {
            characters.erase(characters.begin() + i);
            break;
        }
    }
}

void Level::putBoxOnMap(bool isDestroyable, const int posX, const int posY, sf::Texture &texture) {
    boxes.push_back(new BoxEditor(isDestroyable, posX, posY));
    boxes[boxes.size() - 1]->setTexture(texture);
    if(isDestroyable)
        boxes[boxes.size() - 1]->textureId = std::stoi(chosenAsset.substr(4));
    else
        boxes[boxes.size() - 1]->textureId = std::stoi(chosenAsset.substr(5)) + 4;
    gameBoard[posY][posX] = "box";
}

void Level::putCharacterOnMap(const int posX, const int posY, sf::Texture &texture) {
    std::string charactersColors = "bgry";
    removeCharacterFromMap(charactersColors[int(chosenAsset[10]) - 48]);
    characters.push_back(new CharacterEditor(false, posX, posY, charactersColors[int(chosenAsset[10]) - 48]));
    characters[characters.size() - 1]->setTexture(texture);
    gameBoard[posY][posX] = "character";
}

void Level::draw() {
    window->draw(background);
    for (BoxEditor *box : boxes)
        window->draw(box->sprite);   
    for(CharacterEditor* character : characters)
        window->draw(character->sprite);
}