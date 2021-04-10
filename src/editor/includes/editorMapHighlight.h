#pragma once
#include "level.h"

class MapHighlight : public Object {
    private:
        int fixPositionOnMap(int position);

        bool isCursorOnMap();

        void setRectOnMap();

    public:

        MapHighlight(const sf::Vector2f mousePosition, sf::Texture &texture);

        ~MapHighlight();

};