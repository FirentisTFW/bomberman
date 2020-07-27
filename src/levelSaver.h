#pragma once
#include "levelEditorUI.h"

class LevelSaver {
    
    public:
        std::fstream mapFile;

        LevelSaver();

        ~LevelSaver();

        void saveLevel(const int backgroundId, const std::vector<Box *> &boxes, const std::vector<Character *> &characters);

        void saveBackground(const int backgroundId);

        void saveBoxes(const std::vector<Box *> &boxes);

        void saveCharacters(const std::vector<Character *> &characters);
};