#include "includes/aiPositionChecker.h"

std::array<Point, 4> AiPositionChecker::getSurroundingPositions(const int posX, const int posY) {
    std::array<Point, 4> positions;
    positions[0].posX = posX;
    positions[0].posY = posY - 1;
    positions[1].posX = posX;
    positions[1].posY = posY + 1;
    positions[2].posX = posX - 1;
    positions[2].posY = posY;
    positions[3].posX = posX + 1;
    positions[3].posY = posY;

    return positions;
}
