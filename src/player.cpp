#include "player.h"

Player::Player(bool _isHuman) {
    std::cout << "player created!" << std::endl;

    rect.setSize(sf::Vector2f(50, 50));
    rect.setPosition(0, 0);
    rect.setFillColor(sf::Color::Green);

    if(_isHuman == true) isHuman = true;

    speed = 1;

}

void Player::move(char direction) {
    switch(direction) {
        case 'u':
            std::cout << "move up" << std::endl;
            if(rect.getPosition().y - 50 >= 0) {        // player can move -> still on the map
                rect.move(0, -50);
            }
            break;
        case 'd':
            std::cout << "move down" << std::endl;
            if(rect.getPosition().y + 50 <= 799) {        // player can move -> still on the map
                rect.move(0, +50);
            }
            break;
        case 'l':
            std::cout << "move left" << std::endl;
            if(rect.getPosition().x - 50 >= 0) {        // player can move -> still on the map
                rect.move(-50, 0);
            }
            break;
        case 'r':
            std::cout << "move right" << std::endl;
            if(rect.getPosition().x + 50 <= 799) {        // player can move -> still on the map
                rect.move(50, 0);
            }
            break;
    }
}