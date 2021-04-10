#pragma once
#include "../../editor/includes/levelEditorEventChecker.h"

class EditorExecutor {
    private:
        sf::RenderWindow *window;       
        LevelEditorUI *levelEditorUI;
        Level *level;

    public:
        EditorExecutor(sf::RenderWindow *_window);

        ~EditorExecutor();

        void handleEvent(sf::Event &event);

        void draw();
};