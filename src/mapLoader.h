#pragma once
#include "box.h"
#include "character.h"

namespace mapLoader {
    void loadMap(std::vector<Box *> &boxes, std::vector<Character *> &characters);
}