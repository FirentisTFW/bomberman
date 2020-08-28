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
            surroundingPositions = getSurroundingPositions();
            for(Point point : surroundingPositions) {
                if (gameBoard[point.posY][point.posX] == "box" || gameBoard[point.posY][point.posX] == "character" && !character->frozen)
                    return true;
            }
        }
    }
    return false;
}

std::array<Point, 4> AiBombPlacer::getSurroundingPositions() {
    std::array<Point, 4> positions;
    positions[0].posX = character->posX;
    positions[0].posY = character->posY - 1;
    positions[1].posX = character->posX;
    positions[1].posY = character->posY + 1;
    positions[2].posX = character->posX - 1;
    positions[2].posY = character->posY;
    positions[3].posX = character->posX + 1;
    positions[3].posY = character->posY;

    return positions;
}