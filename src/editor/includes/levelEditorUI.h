#pragma once
#include "../assets/includes/boxEditor.h"
#include "../assets/includes/characterEditor.h"
#include "../../game/includes/textProperties.h"

class LevelEditorUI {
    private:
        sf::RenderWindow *window;
        sf::Font font;

        sf::Texture sideBarTexture;
        sf::Sprite sideBar;

        sf::Text backgroundsText;
        sf::Text boxesText;
        sf::Text wallsText;
        sf::Text charactersText;

        sf::Text save;
        sf::Text reset;
        sf::Text exit;

        void loadTextures();

        void loadFont();

        void loadTexts();

        void loadButtons();

        void loadBackgrounds();

        void loadBoxes();

        void loadWalls();

        void loadCharacters();

    public:
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
        std::array<sf::Texture, 2> backgroundsTexturesFullSize;

        LevelEditorUI(sf::RenderWindow* _window);

        ~LevelEditorUI();

        sf::Texture& getTextureForAsset(std::string asset);

        void draw();
};