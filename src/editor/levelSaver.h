#pragma once
#include "levelEditorUI.h"

class LevelSaver {
    
    public:
        std::fstream mapFile;

        LevelSaver();

        ~LevelSaver();

        void saveLevel(const int backgroundId, const std::vector<BoxEditor *> &boxes, const std::vector<CharacterEditor *> &characters);

        void saveBackground(const int backgroundId);

        void saveBoxes(const std::vector<BoxEditor *> &boxes);

        void saveCharacters(const std::vector<CharacterEditor *> &characters);
};