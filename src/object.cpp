#include "object.h"

bool Object::isPositionOnTheMap(int posX, int posY) {
    if (posY >= 0 && posY < 16 && posX >= 0 && posX < 16)
        return true;
    return false;
}