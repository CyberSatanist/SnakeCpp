#include "lifeInfoBar.h"
#include <LifeGame/Parameters/lifeGameParameters.h>

extern LifeGameParameters lifeGameParameters;


LifeInfoBar::LifeInfoBar(int xStart, int yStart, int xEnd, int yEnd) : InfoBar(xStart, yStart, xEnd, yEnd)
{
    barTitle = "~INFORMATION~";
 
    barChoices = 
    {
        "Cells count",
        "Speed",
        "Turn",
    };

    rows = barChoices.size();
    columns = barChoices.size() / rows;

    firstBarTitle = CellsCount;
    lastBarTitle = Turn;
}


int LifeInfoBar::getParameter(int count)
{
    switch(count) {
        case CellsCount:
            return lifeGameParameters.cellsCount;
            break;
        case Speed:
            return lifeGameParameters.delayDuration;
            break;
        case Turn:
            return lifeGameParameters.turn;
            break;
        default:
            return 0;
    }
}
