#pragma once

#include "../../init.h"
#include "point.h"

class AiPositionChecker {
    public:
        std::array<Point, 4> getSurroundingPositions(const int posX, const int posY);
};