#pragma once

class Player {

    public:
        int lives;
        int score;
        char color;

        Player(char _color);

        ~Player();
};