#ifndef INFO_BAR_H
#define INFO_BAR_H

#include "Bars/bar.h"


class InfoBar : public Bar
{
    public:
        InfoBar(int xStart, int yStart, int xEnd, int yEnd) : Bar(xStart, yStart, xEnd, yEnd) {};
        ~InfoBar() {};

        void drawBar() override;

        virtual int getParameter(int count) { return 0; };

};

#endif