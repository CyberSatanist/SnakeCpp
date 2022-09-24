#ifndef MAP_H
#define MAP_H
#include "../../../Screen/screen.h"

class Map {

    private:
        int** fieldMap;
        int mapSizeX;
        int mapSizeY;
        Screen currentScreen;

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
