#include "player.h"

Player::Player(char _color) {
    color = _color;
    lives = 3;
    score = 0;
}

Player::~Player() {}