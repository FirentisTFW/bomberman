#include "aiMovement.h"

std::string AiMovement::possibleMoves = "udlr";

AiMovement::AiMovement(Character* &_character, std::array<std::array<std::string, 16>, 16> &_gameBoard, std::vector<Bomb *> &_bombs) {
    character = _character;
    gameBoard = _gameBoard;
    bombs = _bombs;
}

AiMovement::~AiMovement() {}

void AiMovement::createCharactersMovement(std::vector<Character *> &characters, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb*> &bombs) {
    for (int i = 1; i < characters.size(); i++) {
        AiMovement AiMovementMovementHandler = AiMovement(characters[i], gameBoard, bombs);
        AiMovementMovementHandler.handleMovement();
    }
}

void AiMovement::handleMovement() {
   while(!didCharacterMove) {
        possibleMove = getRandomMove();
        suggestedXPos = character->getSuggestedXPosition(possibleMove);
        suggestedYPos = character->getSuggestedYPosition(possibleMove);

        character->tryToMove(possibleMove, gameBoard, bombs);

        if(character->didCharacterMove(suggestedXPos, suggestedYPos))
            didCharacterMove = true;
        else {
            savePossibleMove();
            if(allDirectionsTried())
                makeMostOptimalMove();
        }
    }
}

void AiMovement::savePossibleMove() {
    if (!wasThisDirectionAlreadyTried(possibleMove)) {
        triedDirections.push_back(possibleMove);
        dangerOfMoves.push_back(getDangerOfSuggestedMove());
        nubmerOfNextPossibleMoves.push_back(getNumberOfNextPossibleMoves());
    }
}

int AiMovement::getNumberOfNextPossibleMoves() {
    int possibleNextMoves = 0;
    std::array<Point, 4> surroundingPositions = getSurroundingPositions();
    for(Point point : surroundingPositions) {
        if (Object::isPositionOnTheMap(point.posX, point.posY)) {
            if (gameBoard[point.posY][point.posX] == "0" || gameBoard[point.posY][point.posX] == "bonus" || gameBoard[point.posY][point.posX] == "digged_bomb" || gameBoard[point.posY][point.posX] == "character")
                possibleNextMoves++;
        }
    }
    return possibleNextMoves-1;
}

std::array<Point, 4> AiMovement::getSurroundingPositions() {
    std::array<Point, 4> positions;
    positions[0].posX = suggestedXPos;
    positions[0].posY = suggestedYPos - 1;
    positions[1].posX = suggestedXPos;
    positions[1].posY = suggestedYPos + 1;
    positions[2].posX = suggestedXPos - 1;
    positions[2].posY = suggestedYPos;
    positions[3].posX = suggestedXPos + 1;
    positions[3].posY = suggestedYPos;

    return positions;
}

void AiMovement::makeMostOptimalMove() {
    if(!character->frozen && isMovingSaferThanStaying()) {
        int bestMoveIndex = getBestMoveIndex();
        character->move(triedDirections[bestMoveIndex]);
    }
    didCharacterMove = true;
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

char AiMovement::getRandomMove() {
    int randomNumber = rand() % 4;      // 0-3
    return possibleMoves[randomNumber];
}

int AiMovement::getBestMoveIndex() {
    int bestMoveDanger = getDangerOfSafestMovePossible();
    std::vector<int> bestMovesIndexes;
    for (int i = 0; i < dangerOfMoves.size(); i++)
        if (dangerOfMoves[i] == bestMoveDanger)
            bestMovesIndexes.push_back(i);
    if(bestMovesIndexes.size() > 1)
        return getIndexOfMoveWithMostNextPossibleMoves(bestMovesIndexes);
    return bestMovesIndexes[0];
}

int AiMovement::getIndexOfMoveWithMostNextPossibleMoves(const std::vector<int> movesIndexes) {
    int mostPossibleMoves = -1;
    int bestMoveIndex = 0;
    for (int i = 0; i < movesIndexes.size(); i++) {
        if (nubmerOfNextPossibleMoves[movesIndexes[i]] > mostPossibleMoves) {
            mostPossibleMoves = nubmerOfNextPossibleMoves[movesIndexes[i]];
            bestMoveIndex = movesIndexes[i];
        }
    }
    return bestMoveIndex;
}