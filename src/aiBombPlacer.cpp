#include "aiBombPlacer.h"

AiBombPlacer::AiBombPlacer(Character *&_character, std::array<std::array<std::string, 16>, 16> &_gameBoard, std::vector<Bomb *> &_bombs) {
    character = _character;
    gameBoard = _gameBoard;
    bombs = _bombs;
}

AiBombPlacer::~AiBombPlacer() {}

bool AiBombPlacer::isItWorthToPlaceBombHere() {
    if(character->bombLimit > 0) {
        int luck = rand() % 2000 + 1;
        if(luck < 20 || character->specialWeaponCounter > 0) {
            surroundingPositions = getSurroundingPositions(character->posX, character->posY);
            for(Point point : surroundingPositions) {
                if(Object::isPositionOnTheMap(point.posX, point.posY))
                    if (gameBoard[point.posY][point.posX] == "box" || gameBoard[point.posY][point.posX] == "character" && !character->frozen)
                        return true;
            }
        }
    }
    return false;
}
