#ifndef LIFE_TOOLS_BAR_H
#define LIFE_TOOLS_BAR_H

#include "Bars/toolsBar.h"


class LifeToolsBar : public ToolsBar
{
    public:
        LifeToolsBar(int xStart, int yStart, int xEnd, int yEnd);
        ~LifeToolsBar() {};

    private:
        enum barChoicesConst {
            Pause,       Reset,
            SpeedUp,     SpeedDown,
            MoveField,   DrawCells,
            CleanUp,     Exit
        };

        void menuControllSelect() override;

};

#endif