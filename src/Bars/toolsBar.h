#ifndef TOOLS_BAR_H
#define TOOLS_BAR_H

#include "Bars/bar.h"


class ToolsBar : public Bar
{
    public:
        ToolsBar(int xStart, int yStart, int xEnd, int yEnd) : Bar(xStart, yStart, xEnd, yEnd) {};
        ~ToolsBar() {};

        void drawBar() override;
        void menuControllHandler(int key);


    protected:
        virtual void menuControllSelect() {};

};

#endif