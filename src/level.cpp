#include "level.h"

Level::Level(sf::RenderWindow* _window) {
    chosenAsset = "box_0";
    window = _window;
}

Level::~Level() {}

void Level::assetWasChosen(std::string assetName) {
    chosenAsset = assetName;
}

void Level::putAssetOnMap(sf::Vector2f mousePosition) {
    int posXOnBoard = mousePosition.x/50;
    int posYOnBoard = mousePosition.y/50;
    if(gameBoard[posYOnBoard][posXOnBoard] != "0") {
        // TODO: remove asset that is already in this place
    }
    // TODO: check if asset is box
    boxes.push_back(new Box(1, posXOnBoard, posYOnBoard));
    gameBoard[posYOnBoard][posXOnBoard] = "box";
    // TODO: apply Texture to the new crated object
}

void Level::draw() {
    for(Box* box : boxes)
        window->draw(box->rect);   
}