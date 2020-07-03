#include "mapLoader.h"

namespace mapLoader {

    void loadMap(std::vector<Box *> &boxes, std::vector<Character*> &characters) {
        // zaladuj plik
        std::fstream mapFile;
        mapFile.open("maps/testMap.txt", std::ios::in);
        
        if(mapFile.good() && !mapFile.eof()) {

            int boxesCounter;
            int charactersCounter;
                std::string line;
                getline(mapFile, line);


                //  CREATE BOXES FROM FILE
                if (line.find("<Boxes>") != std::string::npos) {
                    getline(mapFile, line);
                    if (line.find("counter") != std::string::npos) {
                        std::string counterString = line.substr(line.find("= ") + 2);
                        boxesCounter = std::stoi(counterString);
                        std::cout << boxesCounter << std::endl;
                        for(int i = 0; i < boxesCounter; i++) {
                            getline(mapFile, line);                 // isDestroyable
                            bool _isDestroyable = std::stoi(line);
                            getline(mapFile, line);                 // posX
                            int _posX = std::stoi(line);
                            getline(mapFile, line);                 // posY
                            int _posY = std::stoi(line);

                            // std::cout << _isDestroyable << " " << _posX << " " << _posY << std::endl;
                            boxes.push_back(new Box(_isDestroyable, _posX, _posY));
                            getline(mapFile, line);                 // isHuman
                        }
                        // return;
                    }
                }

                //  CREATE CHARACTERS FROM FILE
                getline(mapFile, line);
                if (line.find("<Characters>") != std::string::npos) {
                    getline(mapFile, line);
                    if (line.find("counter") != std::string::npos) {
                        std::string counterStringCharacters = line.substr(line.find("= ") + 2);
                        charactersCounter = std::stoi(counterStringCharacters);
                        std::cout << charactersCounter << std::endl;
                        for (int i = 0; i < charactersCounter; i++) {
                            getline(mapFile, line); // isHuman
                            bool _isHuman = std::stoi(line);
                            getline(mapFile, line); // posX
                            int _posX = std::stoi(line);
                            getline(mapFile, line); // posY
                            int _posY = std::stoi(line);
                            getline(mapFile, line); // posY
                            char _color = line[0];

                            // std::cout << _isDestroyable << " " << _posX << " " << _posY << std::endl;
                            characters.push_back(new Character(_isHuman, _posX, _posY, _color));
                            getline(mapFile, line); // isHuman
                        }
                    }
                }

            mapFile.close();
        }
        else {
            std::cout << "Error! Couldn't open the file" << std::endl;
        }
    }
}