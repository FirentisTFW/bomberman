#include "aiBombChecker.h"

std::vector<int> AiBombChecker::getPositionOfClosestBombsVertical(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    std::vector<int> bombsPositions;
    for (int i = posY; i >= 0; i--) {
        if (gameBoard[i][posX] == "bomb")
            bombsPositions.push_back(i);
        else if (gameBoard[i][posX] == "wall" || gameBoard[i][posX] == "box")
            break;
    }
    for (int i = posY; i < gameBoard[0].size(); i++) {
        if (gameBoard[i][posX] == "bomb")
            bombsPositions.push_back(i);
        else if (gameBoard[i][posX] == "wall" || gameBoard[i][posX] == "box")
            break;
    }
    return bombsPositions;
}

std::vector<int> AiBombChecker::getPositionOfClosestBombsHorizontal(const int posX, const int posY, const std::array<std::array<std::string, 16>, 16> &gameBoard) {
    std::vector<int> bombsPositions;
    for (int i = posX; i >= 0; i--) {
        if (gameBoard[posY][i] == "bomb")
            bombsPositions.push_back(i);
        else if (gameBoard[posY][i] == "wall" || gameBoard[posY][i] == "box")
            break;
    }
    for (int i = posX; i < gameBoard[0].size(); i++) {
        if (gameBoard[posY][i] == "bomb")
            bombsPositions.push_back(i);
        else if (gameBoard[posY][i] == "wall" || gameBoard[posY][i] == "box")
            break;
    }
    return bombsPositions;
}

int AiBombChecker::getVerticalDirectionDanger(const int posX, const int posY, const std::vector<int> bombsPositionsVertical, const std::vector<Bomb *> &bombs) {
    int danger = 0;
    for (int i = 0; i < bombsPositionsVertical.size(); i++) {
        for (Bomb *bomb : bombs) {
            if (bomb->posX == posX && bomb->posY == bombsPositionsVertical[i]) {
                if (bomb->posY + bomb->range >= posY && posY >= bomb->posY) 
                    danger = (bomb->posY + bomb->range) - posY + 1;
                else if(bomb->posY - bomb->range <= posY && posY <= bomb->posY)
                    danger = posY - (bomb->posY - bomb->range) + 1;
            }
        }
    }
    return danger;
}

int AiBombChecker::getHorizontalDirectionDanger(const int posX, const int posY, const std::vector<int> bombsPositionsHorizontal, const std::vector<Bomb *> &bombs) {
    int danger = 0;
    for (int i = 0; i < bombsPositionsHorizontal.size(); i++) {
        for (Bomb *bomb : bombs) {
            if (bomb->posY == posY && bomb->posX == bombsPositionsHorizontal[i]) {
                if (bomb->posX + bomb->range >= posX && posX >= bomb->posX)
                    danger = (bomb->posX + bomb->range) - posX + 1;
                else if (bomb->posX - bomb->range <= posX && posX <= bomb->posX)
                    danger = posX - (bomb->posX - bomb->range) + 1;
            }
        }
    }
    return danger;
}
