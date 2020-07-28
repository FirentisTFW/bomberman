#include "level.h"

Level::Level(sf::RenderWindow* _window, sf::Texture &_background) {
    clearGameBoard();
    setBackground(_background, 0);
    chosenAsset = "box_0";
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
    int posXOnBoard = mousePosition.x / 50;
    int posYOnBoard = mousePosition.y / 50;

    makeFieldEmpty(posXOnBoard, posYOnBoard);

    if (chosenAsset.find("box") != std::string::npos) {
        boxes.push_back(new BoxEditor(1, posXOnBoard, posYOnBoard));
        boxes[boxes.size()-1]->setTexture(texture);  
        boxes[boxes.size()-1]->textureId = std::stoi(chosenAsset.substr(4));  
        gameBoard[posYOnBoard][posXOnBoard] = "box";
    }
    else if (chosenAsset.find("wall") != std::string::npos) {
        boxes.push_back(new BoxEditor(0, posXOnBoard, posYOnBoard));
        boxes[boxes.size() - 1]->setTexture(texture);
        boxes[boxes.size()-1]->textureId = std::stoi(chosenAsset.substr(5)) + 4;  
        gameBoard[posYOnBoard][posXOnBoard] = "wall";
    }
    else if (chosenAsset.find("character") != std::string::npos) {
        std::string charactersColors = "bgry";
        removeCharacterFromMap(charactersColors[int(chosenAsset[10]) - 48]);
        characters.push_back(new CharacterEditor(false, posXOnBoard, posYOnBoard, charactersColors[int(chosenAsset[10]) - 48]));
        characters[characters.size() - 1]->setTexture(texture);
        gameBoard[posYOnBoard][posXOnBoard] = "character";
    }
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

void Level::draw() {
    window->draw(background);
    for (BoxEditor *box : boxes)
        window->draw(box->sprite);   
    for(CharacterEditor* character : characters)
        window->draw(character->sprite);
}