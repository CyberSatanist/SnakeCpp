#ifndef LIFE_MAP_H
#define LIFE_MAP_H
#include "../../../Screen/screen.h"

extern Screen currentScreen;

class LifeMap {

    private:
        int** fieldMap;
        int mapSizeX;
        int mapSizeY;

    public:
        enum spaceTypes {Free, Food, Snake, Wall};
        void initMap(int sizeX, int sizeY);
        void drawField();

        int getSizeX();
        int getSizeY();
        int getCell(int cellX, int cellY);
        void setCell(int cellX, int cellY, int color);

};
#endif
