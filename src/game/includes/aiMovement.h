#pragma once
#include "character.h"
#include "point.h"
#include "aiPositionChecker.h"

class AiMovement : AiPositionChecker {
    private:
        Character* character;
        std::array<std::array<std::string, 16>, 16> gameBoard;
        std::vector<Bomb *> bombs;
        bool didCharacterMove = false;
        std::vector<char> triedDirections;
        std::vector<int> dangerOfMoves;
        std::vector<int> nubmerOfNextPossibleMoves;

        char possibleMove;
        int suggestedXPos;
        int suggestedYPos;

        void handleMovement();

        char getRandomMove();

        void savePossibleMove();

        int getNumberOfNextPossibleMoves();

        // std::array<Point, 4> getSurroundingPositions();

        bool isFieldPossibleToStepOn(const Point field);

        void makeMostOptimalMove();

        bool wasThisDirectionAlreadyTried(const char direction);

        int getDangerOfSuggestedMove();

        bool allDirectionsTried();

        bool isMovingSaferThanStaying();

        int getDangerOfSafestMovePossible();

        int getBestMoveIndex();

        int getIndexOfMoveWithMostNextPossibleMoves(const std::vector<int> movesIndexes);

    public:
        AiMovement(Character *&_character, std::array<std::array<std::string, 16>, 16> &_gameBoard, std::vector<Bomb *> &_bombs);

        ~AiMovement();

        static std::string possibleMoves;

        static void createCharactersMovement(std::vector<Character *> &characters, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs);
};