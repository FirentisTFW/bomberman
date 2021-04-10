#pragma once
#include "levelEditorUI.h"

class LevelSaver {
    private:
        std::fstream mapFile;

        int getNumberOfNextMap();

        void updateLevelCounter(int updatedCounter);

        void saveBackground(const int backgroundId);

        void saveBoxes(const std::vector<BoxEditor *> &boxes);

        void saveCharacters(const std::vector<CharacterEditor *> &characters);

    public:

        LevelSaver();

        ~LevelSaver();

        void saveLevel(const int backgroundId, const std::vector<BoxEditor *> &boxes, const std::vector<CharacterEditor *> &characters);
};