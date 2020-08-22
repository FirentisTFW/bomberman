#include "gameTextures.h"

GameTextures::GameTextures() {}

GameTextures::~GameTextures() {}

void GameTextures::loadTextures() {
    backgroundTexture.loadFromFile("images/backgrounds/background_1.png");
    bombTexture.loadFromFile("images/weapons_effects/bomb.png");
    explosionTexture.loadFromFile("images/weapons_effects/explosion.png");

    loadCharactersTextures();

    loadBoxesTextures();

    loadSpecialWeaponsTextures();

    loadBonusesTextures();

    loadIconsTextures();
}

void GameTextures::loadCharactersTextures() {
    for (int i = 1; i < 5; i++)
        charactersTextures[i - 1].loadFromFile("images/characters/character_" + std::to_string(i) + ".png");
}

void GameTextures::loadBoxesTextures() {
    for (int i = 1; i < 5; i++)
        boxesTextures[i - 1].loadFromFile("images/boxes/box_" + std::to_string(i) + ".png");

    for (int i = 1; i < 5; i++)
        boxesTextures[i + 3].loadFromFile("images/boxes/stone_wall_" + std::to_string(i) + ".png");
}

void GameTextures::loadSpecialWeaponsTextures() {
    specialWeaponsTextures[0].loadFromFile("images/weapons_effects/fire.png");
    specialWeaponsTextures[1].loadFromFile("images/weapons_effects/ice.png");
}

void GameTextures::loadIconsTextures() {
    iconsTextures[0].loadFromFile("images/special_weapons_icons/i_fire.png");
    iconsTextures[1].loadFromFile("images/special_weapons_icons/i_ice.png");
    iconsTextures[2].loadFromFile("images/special_weapons_icons/i_digged_bomb.png");
}

void GameTextures::loadBonusesTextures() {
    bonusesTextures[0].loadFromFile("images/bonuses/b_fire.png");
    bonusesTextures[1].loadFromFile("images/bonuses/b_ice.png");
    bonusesTextures[2].loadFromFile("images/bonuses/b_range.png");
    bonusesTextures[3].loadFromFile("images/bonuses/b_bomb.png");
    bonusesTextures[4].loadFromFile("images/bonuses/b_shield.png");
    bonusesTextures[5].loadFromFile("images/bonuses/b_live.png");
    bonusesTextures[6].loadFromFile("images/bonuses/b_push.png");
    bonusesTextures[7].loadFromFile("images/bonuses/b_speed.png");
    bonusesTextures[8].loadFromFile("images/bonuses/b_digged_bomb.png");
}