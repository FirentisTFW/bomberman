#pragma once
#include "box.h"
#include "character.h"

namespace mapLoader {
    void loadMap(std::vector<Box *> &boxes, std::vector<Character *> &characters, std::array<sf::Texture, 10> &boxesTextures, std::array<sf::Texture, 4> &charactersTextures);
}