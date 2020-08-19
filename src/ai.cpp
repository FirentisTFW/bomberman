#include "ai.h"

std::string Ai::possibleMoves = "udlr";

void Ai::createCharactersMovement(std::vector<Character *> &characters, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    for (int i = 1; i < characters.size(); i++) {
        bool didCharacterMove = false;
        std::vector<char> triedDirections;
        std::vector<int> dangerOfMoves;
        while(!didCharacterMove) {
            char possibleMove = getRandomMove();
            int suggestedXPos = characters[i]->getSuggestedXPosition(possibleMove);
            int suggestedYPos = characters[i]->getSuggestedYPosition(possibleMove);
            if (characters[i]->isPositionOnTheMap(suggestedXPos, suggestedYPos)) {
                characters[i]->tryToMove(possibleMove, gameBoard, bombs);
                didCharacterMove = true;
            }
            else {
                if(std::find(triedDirections.begin(), triedDirections.end(), possibleMove) == triedDirections.end()) {
                    triedDirections.push_back(possibleMove);
                    if(triedDirections.size() == 4)        // no safe move - character stays on current position
                        didCharacterMove = true;
                }
            }
            // dangerOfMoves.push_back(characters[i]->getDangerOfMove(suggestedXPos, suggestedYPos, gameBoard, bombs));
            // int bestMoveIndex = std::min_element(dangerOfMoves.begin(), dangerOfMoves.end()) - dangerOfMoves.begin();
            // characters[i]->tryToMove(triedDirections[bestMoveIndex], gameBoard, bombs);
        }
    }
}


char Ai::getRandomMove() {
    int randomNumber = rand() % 4;      // 0-3
    return possibleMoves[randomNumber];
}