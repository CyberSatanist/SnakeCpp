#include "lifeToolsBar.h"
#include <LifeGame/Parameters/lifeGameParameters.h>

extern LifeGameParameters lifeGameParameters;


LifeToolsBar::LifeToolsBar(int xStart, int yStart, int xEnd, int yEnd) : ToolsBar(xStart, yStart, xEnd, yEnd)
{
    barTitle = "~TOOLS~";
 
    barChoices =
    {
        "Pause",              "Reset",
        "Speed++",            "Speed--",
        "Move Field",         "Draw cells",
        "Clean field",           "Exit",
    };

    rows = 2;
    columns = barChoices.size() / rows;

    firstBarTitle = Pause;
    lastBarTitle = Exit;
}


void LifeToolsBar::menuControllSelect()
{
    if (currentChoice == barChoicesConst::Pause){
        if (lifeGameParameters.pauseOn) {
            lifeGameParameters.pauseOn = false;
        } else {
            lifeGameParameters.pauseOn = true;
        }
    } else if (currentChoice == barChoicesConst::Reset){
        lifeGameParameters.reset = true;
    } else if (currentChoice == barChoicesConst::SpeedUp){
        if (lifeGameParameters.delayDuration == 1) {
            lifeGameParameters.delayDuration = 200;
        } else {
            lifeGameParameters.delayDuration--;
        }
        timeout(lifeGameParameters.delayDuration);
    } else if (currentChoice == barChoicesConst::SpeedDown){
        if (lifeGameParameters.delayDuration == 200) {
            lifeGameParameters.delayDuration = 1;
        } else {
            lifeGameParameters.delayDuration++;
        }
        timeout(lifeGameParameters.delayDuration);
    } else if (currentChoice == barChoicesConst::MoveField){
        lifeGameParameters.moveField = true;
    } else if (currentChoice == barChoicesConst::DrawCells){
        lifeGameParameters.drawCells = true;
        lifeGameParameters.pauseOn = true;
    } else if (currentChoice == barChoicesConst::CleanUp){
        lifeGameParameters.clean = true;
    } else if (currentChoice == barChoicesConst::Exit){
        lifeGameParameters.gameOn = false;
    }
}