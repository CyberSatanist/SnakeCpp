#ifndef FIELD_H
#define FIELD_H

#include "Screen/screen.h"

extern Screen currentScreen;

class Field 
{
    protected:
        int beginX = 0;
        int beginY = 0;
        int sizeX;
        int sizeY;
        int currentBeginX = 0;
        int currentBeginY = 0;
        int currentSizeX;
        int currentSizeY;
        int fullSizeX;
        int fullSizeY;

        int **fieldMap = nullptr;

    public:
        Field(int currentX, int currentY, int fullX, int fullY);
        Field(const Field &field);
        ~Field();
        Field& operator= (const Field &field);

        enum spaceTypes {Free, Food, Snake, Wall, Cell, Frame, Cursor, Nothing};
        
        void drawField();

        inline int getBeginX() const { return beginX; };
        inline int getBeginY() const { return beginY; };
        inline int getSizeX() const { return sizeX; };
        inline int getSizeY() const { return sizeY; };
        inline int getCurrentBeginX() const { return currentBeginX; };
        inline int getCurrentBeginY() const { return currentBeginY; };
        inline int getCurrentSizeX() const { return currentSizeX; };
        inline int getCurrentSizeY() const { return currentSizeY; };
        inline int getFullSizeX() const { return fullSizeX; };
        inline int getFullSizeY() const { return fullSizeY; };

        void moveFieldUp();
        void moveFieldDown();
        void moveFieldLeft();
        void moveFieldRight();

        inline int getCell(int cellX, int cellY) const { return fieldMap[cellX][cellY]; };
        inline void setCell(int cellX, int cellY, int color) { fieldMap[cellX][cellY] = color; };

        virtual void drawCell(int cellX, int cellY) {};

};

#endif