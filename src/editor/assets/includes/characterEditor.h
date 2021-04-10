#pragma once
#include "../../../game/includes/object.h"

class CharacterEditor: public Object {

public:
    bool isHuman;               // is character controlled by human or is it AI
    char color;

    CharacterEditor(bool isHuman, int _posX, int _posY, char _color);
    ~CharacterEditor();
};