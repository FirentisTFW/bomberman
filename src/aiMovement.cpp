#include "aiMovement.h"

std::string AiMovement::possibleMoves = "udlr";

AiMovement::AiMovement(Character* &_character, std::array<std::array<std::string, 16>, 16> &_gameBoard, std::vector<Bomb *> &_bombs) {
    character = _character;
    gameBoard = _gameBoard;
    bombs = _bombs;
}

AiMovement::~AiMovement() {}

void AiMovement::handleMovement() {
   while(!didCharacterMove) {
        possibleMove = getRandomMove();
        suggestedXPos = character->getSuggestedXPosition(possibleMove);
        suggestedYPos = character->getSuggestedYPosition(possibleMove);

        character->tryToMove(possibleMove, gameBoard, bombs);

        if(character->didCharacterMove(suggestedXPos, suggestedYPos))
            didCharacterMove = true;
        else
            characterDidNotMove();
    }
}

void AiMovement::characterDidNotMove() {
    if(!wasThisDirectionAlreadyTried(possibleMove)) {
        triedDirections.push_back(possibleMove);
        dangerOfMoves.push_back(getDangerOfSuggestedMove());
        if(allDirectionsTried()) {
            if(isMovingSaferThanStaying()) {
                int bestMoveIndex = std::min_element(dangerOfMoves.begin(), dangerOfMoves.end()) - dangerOfMoves.begin();
                character->move(triedDirections[bestMoveIndex]);
            }
            didCharacterMove = true;
        }
    }
}

bool AiMovement::wasThisDirectionAlreadyTried(const char direction) {
    return std::find(triedDirections.begin(), triedDirections.end(), direction) != triedDirections.end();
}

int AiMovement::getDangerOfSuggestedMove() {
    if (!character->isMovePossible(suggestedXPos, suggestedYPos, possibleMove, gameBoard, bombs))
        return 200;
    else
        return character->getDangerOfMove(suggestedXPos, suggestedYPos, gameBoard, bombs);
}

bool AiMovement::allDirectionsTried() {
    return triedDirections.size() == 4;
}

bool AiMovement::isMovingSaferThanStaying() {
    int safestMoveDanger = getDangerOfSafestMovePossible();
    int stayOnPositionDanger = character->getDangerOfCurrentPosition(gameBoard, bombs);
    return safestMoveDanger < stayOnPositionDanger;
}

int AiMovement::getDangerOfSafestMovePossible() {
    return *std::min_element(dangerOfMoves.begin(), dangerOfMoves.end());
}

void AiMovement::createCharactersMovement(std::vector<Character *> &characters, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    for (int i = 1; i < characters.size(); i++) {
        AiMovement AiMovementMovementHandler = AiMovement(characters[i], gameBoard, bombs);
        AiMovementMovementHandler.handleMovement();
    }
}

char AiMovement::getRandomMove() {
    int randomNumber = rand() % 4;      // 0-3
    return possibleMoves[randomNumber];
}