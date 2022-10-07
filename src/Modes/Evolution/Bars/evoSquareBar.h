#ifndef EVO_SQUARE_BAR
#define EVO_SQUARE_BAR

#include <Bars/squareBar.h>
#include <Bars/squareBar.h>
#include <Field/field.h>


class EvoSquareBar : public SquareBar
{
    public:
        void initField(Field thatField);
        void drawMap(Field thatField);

    private:

        Field field;
        int mapSizeX;
        int mapSizeY;
        int fieldSizeX;
        int fieldSizeY;
        int stepX;
        int stepY;

        void drawCell(int cellX, int cellY, int color);
        int getColor(int mapX, int mapY, int stepX, int stepY);
};

#endif