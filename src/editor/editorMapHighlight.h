#pragma once
#include "level.h"

class MapHighlight : public Object {

    public:

        MapHighlight(const sf::Vector2f mousePosition, sf::Texture &texture);

        ~MapHighlight();

        int fixPositionOnMap(int position);

        bool isCursorOnMap();

        void setRectOnMap();
};