#ifndef EVO_TOOLS_BAR_H
#define EVO_TOOLS_BAR_H

#include "Bars/toolsBar.h"


class EvoToolsBar : public ToolsBar 
{
    public:
        EvoToolsBar(int xStart, int yStart, int xEnd, int yEnd);
        ~EvoToolsBar() {};

        bool pauseOn = false;


    private:
        enum barChoicesConst {
            SpeedUp, SpeedDown, FoodUp, FoodDown, MutPlus, MutMinus,
            TurnsToDeathUp, TurnsToDeathDown, BordersUp, BordersDown, Pause, Exit
        };

        void menuControllSelect() override;

};

#endif