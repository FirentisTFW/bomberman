#pragma once

class Player {

    public:
        int lives;
        int score;
        // char color;
        int color;

        Player(int _color);

        ~Player();
};