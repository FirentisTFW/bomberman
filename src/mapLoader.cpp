#include "mapLoader.h"

MapLoader::MapLoader() {}

MapLoader::~MapLoader() {}

void MapLoader::loadMap(std::vector<Box *> &boxes, std::vector<Character *> &characters, std::array<sf::Texture, 10> &boxesTextures, std::array<sf::Texture, 4> &charactersTextures, sf::Texture &backgroundTexture) {
    mapFile.open("maps/native/map_1.txt", std::ios::in);
    if(mapFile.good()) {
        loadBackground(backgroundTexture);
        loadBoxes(boxes, boxesTextures);
        loadCharacters(characters, charactersTextures);
        mapFile.close();
    }
    else {
        std::cout << "Couldn't open the file!" << std::endl;
    }
}

void MapLoader::loadBackground(sf::Texture &backgroundTexture) {
    std::string line;
    getline(mapFile, line);
    std::string backgroundIdString = line.substr(line.find("= ") + 2);
    int backgroundId = std::stoi(backgroundIdString);
    backgroundTexture.loadFromFile("images/backgrounds/background_" + std::to_string(backgroundId+1) + ".png");
}

void MapLoader::loadBoxes(std::vector<Box *> &boxes, std::array<sf::Texture, 10> &boxesTextures) {
    int boxesCounter;
    std::string line;
    getline(mapFile, line);

    if (line.find("<Boxes>") != std::string::npos) {
        getline(mapFile, line);
        boxesCounter = getCounter(line);
        if (boxesCounter != -1) {
            for(int i = 0; i < boxesCounter; i++) {
                getline(mapFile, line);                 // isDestroyable
                bool _isDestroyable = std::stoi(line);
                getline(mapFile, line);                 // posX
                int _posX = std::stoi(line);
                getline(mapFile, line);                 // posY
                int _posY = std::stoi(line);
                getline(mapFile, line);                 // textureId
                int _textureId = std::stoi(line);

                boxes.push_back(new Box(_isDestroyable, _posX, _posY));                                 // create box
                boxes[boxes.size()-1]->sprite.setTexture(boxesTextures[_textureId]);                    // set texture
                boxes[boxes.size()-1]->sprite.setPosition(boxes[boxes.size()-1]->rect.getPosition());

                getline(mapFile, line);                 
            }
        }
    }
}

void MapLoader::loadCharacters(std::vector<Character *> &characters, std::array<sf::Texture, 4> &charactersTextures) {
    int charactersCounter;
    std::string line;
    getline(mapFile, line);

    if (line.find("<Characters>") != std::string::npos) {
        getline(mapFile, line);
        charactersCounter = getCounter(line);
        if (charactersCounter != -1) {
            for (int i = 0; i < charactersCounter; i++) {
                getline(mapFile, line); // isHuman
                bool _isHuman = std::stoi(line);
                getline(mapFile, line); // posX
                int _posX = std::stoi(line);
                getline(mapFile, line); // posY
                int _posY = std::stoi(line);
                getline(mapFile, line); // color
                char _color = line[line.find_first_of("bgry")];

                characters.push_back(new Character(_isHuman, _posX, _posY, _color));
                int textureId = 0;
                if(_color == 'b') textureId = 0;
                else if(_color == 'g') textureId = 1;
                else if(_color == 'r') textureId = 2;
                else if(_color == 'y') textureId = 3;

                characters[characters.size()-1]->setTexture(charactersTextures[textureId]);
                characters[characters.size() - 1]->sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
                getline(mapFile, line);
            }
        }
    }
}

int MapLoader::getCounter(const std::string line) {
    if (line.find("counter") != std::string::npos) {
        std::string counterString = line.substr(line.find("= ") + 2);
        int counter = std::stoi(counterString);
        return counter;
    }
    return -1;
}