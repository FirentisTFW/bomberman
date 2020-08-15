#include "ai.h"

std::string Ai::possibleMoves = "udlr";

void Ai::createCharactersMovement(std::vector<Character *> &characters, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    for (int i = 1; i < characters.size(); i++) {
        bool didCharacterMove = false;
        std::set<char> triedDirections; 
        while(!didCharacterMove) {
            char possibleMove = getRandomMove();
            int suggestedXPos = characters[i]->getSuggestedXPosition(possibleMove);
            int suggestedYPos = characters[i]->getSuggestedYPosition(possibleMove);
            if (characters[i]->isPositionOnTheMap(suggestedXPos, suggestedYPos)) {
                characters[i]->shouldCharacterMove(possibleMove, gameBoard, bombs);
                didCharacterMove = true;
            }
            else {
                triedDirections.insert(possibleMove);
                if(triedDirections.size() == 4)         // no safe move - character stays on current position               
                    didCharacterMove = true;
            }
        }
    }
}

// bool Ai::isTimeForMovement() {
//     return movementFramerate == 10;
// }

char Ai::getRandomMove() {
    int randomNumber = rand() % 4;      // 0-3
    return possibleMoves[randomNumber];
}

bool Ai::isMoveSafe(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    return isMovePossible(posX, posY, gameBoard);
    // TODO: check for bombs danger
}

bool Ai::isMovePossible(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    return gameBoard[posY][posX] != "bomb" && gameBoard[posY][posX] != "box" && gameBoard[posY][posX] != "wall";
}

// bool Ai::canCharacterPlaceBomb(const int availableBombs) {

// }