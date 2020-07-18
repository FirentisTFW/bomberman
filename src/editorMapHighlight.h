#pragma once
#include "level.h"

class MapHighlight {

    public:

        int posX;
        int posY;
        sf::RectangleShape rect;

        MapHighlight(const sf::Vector2f mousePosition);

        ~MapHighlight();

        int fixPositionOnMap(int position);

        bool isCursorOnMap();

        void setRectOnMap();
};