#include "lifeToolsBar.h"
#include <LifeGame/Parameters/lifeGameParameters.h>

extern LifeGameParameters lifeGameParameters;


LifeToolsBar::LifeToolsBar(int xStart, int yStart, int xEnd, int yEnd) : ToolsBar(xStart, yStart, xEnd, yEnd)
{
    barTitle = "~TOOLS~";
 
    barChoices =
    {
        "Save current state",
        "Load state",
        "Move Left",
        "Move Right",
        "Move Up",
        "Move Down",
        "Pause",
        "Exit",
    };

    rows = 2;
    columns = barChoices.size() / rows;

    firstBarTitle = Save;
    lastBarTitle = Exit;
}


void LifeToolsBar::menuControllSelect()
{
    if (currentChoice == barChoicesConst::Save){
    } else if (currentChoice == barChoicesConst::Load){
    } else if (currentChoice == barChoicesConst::Left){
    } else if (currentChoice == barChoicesConst::Right){
    } else if (currentChoice == barChoicesConst::Up){
    } else if (currentChoice == barChoicesConst::Down){
    } else if (currentChoice == barChoicesConst::Pause){
    } else if (currentChoice == barChoicesConst::Exit){
        lifeGameParameters.gameOn = false;
    }
}