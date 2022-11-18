#ifndef FIELD_H
#define FIELD_H

#include <Screen/screen.h>

extern Screen currentScreen;

class Field {
    
        
    public:
        int** fieldMap = nullptr;
        int currentBeginX = 0;
        int currentBeginY = 0;
        int currentSizeX;
        int currentSizeY;
        int fullSizeX;
        int fullSizeY;

        enum spaceTypes {Free, Food, Snake, Wall, Cell, Nothing};
        void initField(int currentX, int currentY, int fullX, int fullY);
        void drawField();

        int getCurrentBeginX();
        int getCurrentBeginY();
        int getCurrentSizeX();
        int getCurrentSizeY();
        
        int getFullSizeX();
        int getFullSizeY();

        void moveFieldUp();
        void moveFieldDown();
        void moveFieldLeft();
        void moveFieldRight();

        int getCell(int cellX, int cellY);
        void setCell(int cellX, int cellY, int color);
        void deleteField();


        virtual void drawCell(int cellX, int cellY) {};

};

#endif