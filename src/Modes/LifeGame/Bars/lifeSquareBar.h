#ifndef LIFE_SQUARE_BAR
#define LIFE_SQUARE_BAR

#include "Bars/squareBar.h"
#include "LifeGame/Field/lifeField.h"


class LifeSquareBar : public SquareBar
{
    public:
        LifeSquareBar(int xStart, int yStart, int xEnd, int yEnd);
        ~LifeSquareBar() {};

        void drawMap(const LifeField &field);


    private:
        int mapSizeX;
        int mapSizeY;
        int fieldSizeX = 0;
        int fieldSizeY = 0;
        int stepX = 0;
        int stepY = 0;

        void drawCell(int cellX, int cellY, int color);
        int getColor(int mapX, int mapY, int stepX, int stepY, const LifeField &field);
};

#endif