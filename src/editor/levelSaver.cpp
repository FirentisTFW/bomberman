#include "levelSaver.h"

LevelSaver::LevelSaver() {
    
}

LevelSaver::~LevelSaver() {}

void LevelSaver::saveLevel(const int backgroundId, const std::vector<BoxEditor *> &boxes, const std::vector<CharacterEditor *> &characters) {
    mapFile.open("maps/map_2.txt", std::ios::out);
    if(mapFile.good()) {
        saveBackground(backgroundId);
        saveBoxes(boxes);
        saveCharacters(characters);
        mapFile.close();
    }
    else {
        std::cout << "Couldn't open the file!" << std::endl;
    }
}

void LevelSaver::saveBackground(const int backgroundId) {
    mapFile << "Background = " + std::to_string(backgroundId) + "\n";
}

void LevelSaver::saveBoxes(const std::vector<BoxEditor *> &boxes) {
    mapFile << "<Boxes>\n";
    mapFile << "counter = " + std::to_string(boxes.size()) + "\n";
    for(BoxEditor* box : boxes) {
        mapFile << std::to_string(box->isDestroyable) + "\n";
        mapFile << std::to_string(box->posX) + "\n";
        mapFile << std::to_string(box->posY) + "\n";
        mapFile << std::to_string(box->textureId) + "\n\n";
    }
}

void LevelSaver::saveCharacters(const std::vector<CharacterEditor *> &characters) {
    mapFile << "<Characters>\n";
    mapFile << "counter = " + std::to_string(characters.size()) + "\n";
    for(CharacterEditor* character : characters) {
        mapFile << std::to_string(character->isHuman) + "\n";
        mapFile << std::to_string(character->posX) + "\n";
        mapFile << std::to_string(character->posY) + "\n";
        std::string color = "";
        color += character->color;
        mapFile << color + "\n\n";
    }
}