#pragma once
#include "../../../game/includes/object.h"

class BoxEditor : public Object {
    public:
        bool isDestroyable;
        int textureId;

        BoxEditor(bool _isDestroyable, int _posX, int _posY);
        ~BoxEditor();
};