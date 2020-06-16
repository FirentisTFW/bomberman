#include "object.h"

class Box : public Object {
    public:
        bool isDestroyable;

        Box(bool _isDestroyable, int _posX, int _posY);
        ~Box();
};