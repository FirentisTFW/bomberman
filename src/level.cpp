#include "level.h"

Level::Level(sf::RenderWindow* _window) {
    chosenAsset = "box_0";
    window = _window;
}

Level::~Level() {}

void Level::assetWasChosen(std::string assetName) {
    chosenAsset = assetName;
}

void Level::putAssetOnMap(sf::Vector2f mousePosition, sf::Texture &texture) {
    int posXOnBoard = mousePosition.x / 50;
    int posYOnBoard = mousePosition.y / 50;

    makeFieldEmpty(posXOnBoard, posYOnBoard);

    if (chosenAsset.find("box") != std::string::npos) {
        boxes.push_back(new Box(1, posXOnBoard, posYOnBoard));
        boxes[boxes.size()-1]->setTexture(texture);  
        gameBoard[posYOnBoard][posXOnBoard] = "box";
    }
    else if (chosenAsset.find("wall") != std::string::npos) {
        boxes.push_back(new Box(0, posXOnBoard, posYOnBoard));
        boxes[boxes.size() - 1]->setTexture(texture);
        gameBoard[posYOnBoard][posXOnBoard] = "wall";
    }
    else if (chosenAsset.find("character") != std::string::npos) {
        std::string charactersColors = "bgry";
        characters.push_back(new Character(false, posXOnBoard, posYOnBoard, charactersColors[chosenAsset[10]]));
        characters[characters.size() - 1]->setTexture(texture);
        gameBoard[posYOnBoard][posXOnBoard] = "character";
    }

}

void Level::makeFieldEmpty(const int posX, const int posY) {
    if (gameBoard[posY][posX] != "0")
        checkWhatAssetIsOnPosition(posX, posY);
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
    for(Box* box : boxes)
        window->draw(box->sprite);   
    for(Character* character : characters)
        window->draw(character->sprite);
}