#pragma once
#include "../init.h"
#include "../textProperties.h"

class MainMenu {
    private:
        sf::RenderWindow *window;
        sf::Sprite background;
        sf::Texture backgroundTexture;
        sf::Font font;
        sf::Text title;
        std::array<sf::Text, 6> buttonsTexts;

        static std::array<std::string, 6> stringsForButtonsTexts;

        void setBackground();

        void loadFont();

        void loadTitle();

        void loadTexts();

        void centerTextInButtons();

        void loadButtons();

    public:
        std::array<sf::RectangleShape, 6> buttons;

        MainMenu(sf::RenderWindow *_window);

        ~MainMenu();

        void setBackgroundTexture();

        void draw();
};