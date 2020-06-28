#pragma once
#include "object.h"

class DiggedBomb : public Object {
    public:

        char color;

        DiggedBomb(int _posX, int _posY, char _color);

        ~DiggedBomb();

};