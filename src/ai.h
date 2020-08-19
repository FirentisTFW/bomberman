#pragma once
#include "character.h"

class Ai {
    public:
        static std::string possibleMoves;

        static void createCharactersMovement(std::vector<Character *> &characters, std::array<std::array<std::string, 16>, 16> &gameBoard, std::vector<Bomb *> &bombs);

        static char getRandomMove();

};