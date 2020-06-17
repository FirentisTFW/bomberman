#include "explosion.h"

Explosion::Explosion(int _posX, int _posY, char color) {

    posX = _posX;
    posY = _posY;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::Yellow);
    
    timeToLive = 60;
}

Explosion::~Explosion() {}

void Explosion::checkForInactiveExplosions(std::vector<Explosion*> &explosions) {
    int explosionsSize = explosions.size();
    for (int i = 0; i < explosionsSize; i++) {
        explosions[i]->timeToLive--;
        if (explosions[i]->timeToLive <= 0) {
            explosions.erase(explosions.begin() + i);
            explosionsSize = explosions.size();
            i--;
        } 
    }
    
}

