#pragma once
#include "object.h"

namespace textProperties {
    
    void setProperties(sf::Text &text, int size, int posX, int posY);

    void setLetterSpacing(sf::Text &text, int numberOfSpaces);
}