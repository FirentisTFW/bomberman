#include "includes/explosion.h"

Explosion::Explosion(int _posX, int _posY, char _color, sf::Texture &texture) {

    posX = _posX;
    posY = _posY;
    color = _color;
    animationCounter = 0;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(posX * 50, posY * 50);
    rect.setFillColor(sf::Color::Yellow);

    timeToLive = 60;

    setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
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

