#pragma once
#include "init.h"

class Object {
    public:
        sf::RectangleShape rect; 
        sf::Sprite sprite;
        int posX;                       // 0-15  | each point represents 50px on the map
        int posY;                       // 0-15  | each point represents 50px on the map    
};