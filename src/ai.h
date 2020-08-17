#pragma once
#include "character.h"

class Ai {
    public:
        static int movementFramerate;

        static std::string possibleMoves;

        static void createCharactersMovement(std::vector<Character *> &characters, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs);

        static bool isTimeForMovement();

        static char getRandomMove();

        static bool isMoveSafe(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard);

        static bool isMovePossible(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard);

};