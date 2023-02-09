#ifndef SQUARE_BAR_H
#define SQUARE_BAR_H

#include "Bars/bar.h"


class SquareBar : public Bar
{
    public:
        SquareBar(int xStart, int yStart, int xEnd, int yEnd) : Bar(xStart, yStart, xEnd, yEnd) {};
        ~SquareBar() {};

};

#endif