#ifndef EVO_SQUARE_BAR
#define EVO_SQUARE_BAR

#include "Bars/squareBar.h"
#include "Field/field.h"


class EvoSquareBar : public SquareBar
{
    public:
        EvoSquareBar(int xStart, int yStart, int xEnd, int yEnd);
        ~EvoSquareBar() {};

        void drawMap(const Field &field);


    private:
        int mapSizeX;
        int mapSizeY;
        int fieldSizeX = 0;
        int fieldSizeY = 0;
        int stepX = 0;
        int stepY = 0;

        void drawCell(int cellX, int cellY, int color);
        int getColor(int mapX, int mapY, int stepX, int stepY, const Field &field);
};

#endif