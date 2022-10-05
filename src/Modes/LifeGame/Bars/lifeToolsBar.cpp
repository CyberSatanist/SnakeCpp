#include "lifeToolsBar.h"
#include <LifeGame/Parameters/lifeGameParameters.h>

extern LifeGameParameters lifeGameParameters;


void LifeToolsBar::menuControllSelect()
{
    if (currentChoice == toolsBarChoicesConst::Save){
    } else if (currentChoice == toolsBarChoicesConst::Load){
    } else if (currentChoice == toolsBarChoicesConst::Left){
    } else if (currentChoice == toolsBarChoicesConst::Right){
    } else if (currentChoice == toolsBarChoicesConst::Up){
    } else if (currentChoice == toolsBarChoicesConst::Down){
    } else if (currentChoice == toolsBarChoicesConst::Pause){
    } else if (currentChoice == toolsBarChoicesConst::Exit){
        lifeGameParameters.gameOn = false;
    }
}


void LifeToolsBar::writeString(int count)
{
    const char *string = toolsBarChoices[count].c_str();
    currentScreen.writeText(string);
}