#pragma once
#include "object.h"

class Box : public Object {
    public:
        bool isDestroyable;
        int textureId;

        Box(bool _isDestroyable, int _posX, int _posY);
        ~Box();
};