#pragma once
#include "character.h"

class AiMovement {
    private:
        Character* character;
        std::array<std::array<std::string, 16>, 16> gameBoard;
        std::vector<Bomb *> bombs;
        bool didCharacterMove = false;
        std::vector<char> triedDirections;
        std::vector<int> dangerOfMoves;

        char possibleMove;
        int suggestedXPos;
        int suggestedYPos;

    public:
        AiMovement(Character *&_character, std::array<std::array<std::string, 16>, 16> &_gameBoard, std::vector<Bomb *> &_bombs);

        ~AiMovement();

        static std::string possibleMoves;

        static void createCharactersMovement(std::vector<Character *> &characters, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs);

        void handleMovement();

        void savePossibleMove();

        void makeMostOptimalMove();

        bool wasThisDirectionAlreadyTried(const char direction);

        int getDangerOfSuggestedMove();

        bool allDirectionsTried();

        bool isMovingSaferThanStaying();

        int getDangerOfSafestMovePossible();

        static char getRandomMove();

        // static int getDangerOfMove(const int posX, const int posY, char direction, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs);

};