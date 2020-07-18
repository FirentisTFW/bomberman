#include "editorMapHighlight.h"

MapHighlight::MapHighlight(sf::Vector2f mousePosition) {

    posX = fixPositionOnMap(mousePosition.x);
    posY = fixPositionOnMap(mousePosition.y);

    if(isCursorOnMap())
        setRectOnMap();
}

MapHighlight::~MapHighlight() {}

int MapHighlight::fixPositionOnMap(int position) {
    if(position < 0)
        return -1;
    return 50 * (position/50);
}

bool MapHighlight::isCursorOnMap() {
    return posX <= 750 && posX > -1 && posY <= 750 && posY > -1;
}

void MapHighlight::setRectOnMap() {
    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX, posY);
    rect.setFillColor(sf::Color::Magenta);
}
