#ifndef LIFE_INFO_BAR_H
#define LIFE_INFO_BAR_H

#include "Bars/infoBar.h"

class LifeInfoBar : public InfoBar
{
    public:
        LifeInfoBar(int xStart, int yStart, int xEnd, int yEnd);
        ~LifeInfoBar() {};


    private:
        enum barChoicesConst {CellsCount, Speed, Turn};

        int getParameter(int count) override;

};

#endif