#ifndef LIFE_TOOLS_BAR_H
#define LIFE_TOOLS_BAR_H

#include "Bars/toolsBar.h"


class LifeToolsBar : public ToolsBar
{
    public:
        LifeToolsBar(int xStart, int yStart, int xEnd, int yEnd);
        ~LifeToolsBar() {};

    private:
        enum barChoicesConst {Save, Load, Left, Right, Up, Down, Pause, Exit};

        void menuControllSelect() override;

};

#endif