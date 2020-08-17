#pragma once
#include "bomb.h"

class AiBombChecker {
    public:
        static std::vector<int> getPositionOfClosestBombsVertical(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard);      // -1 means there are no bombs in this direction

        static std::vector<int> getPositionOfClosestBombsHorizontal(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard); // -1 means there are no bombs in this direction

        static bool isVerticalDirectionSafe(const int posX, const int posY, const std::vector<int> bombsPositionsVertical, const std::vector<Bomb *> &bombs);

        static bool isHorizontalDirectionSafe(const int posX, const int posY, const std::vector<int> bombsPositionsHorizontal, const std::vector<Bomb *> &bombs);
};