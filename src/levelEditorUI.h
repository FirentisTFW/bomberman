#pragma once
#include "box.h"
#include "character.h"
#include "textProperties.h"

class LevelEditorUI {

    public:
        sf::RenderWindow* window;              

        sf::Texture sideBarTexture;
        sf::Sprite sideBar;

        sf::Font font;

        sf::Text backgroundsText;
        sf::Text boxesText;
        sf::Text wallsText;
        sf::Text charactersText;

        sf::Text save;
        sf::Text reset;
        sf::Text exit;
        sf::RectangleShape saveButton;
        sf::RectangleShape resetButton;
        sf::RectangleShape exitButton;

        std::array<sf::Sprite, 4> boxes;
        std::array<sf::Sprite, 4> walls;
        std::array<sf::Sprite, 4> characters;
        std::array<sf::Sprite, 2> backgrounds;

        std::array<sf::Texture, 4> boxesTextures;
        std::array<sf::Texture, 4> wallsTextures;
        std::array<sf::Texture, 4> charactersTextures;
        std::array<sf::Texture, 2> backgroundsTextures;

        LevelEditorUI(sf::RenderWindow* _window);

        ~LevelEditorUI();

        void loadTextures();

        void loadFont();

        void loadTexts();

        void loadButtons();

        void loadBackgrounds();

        void loadBoxes();

        void loadWalls();

        void loadCharacters();

        void draw();
};