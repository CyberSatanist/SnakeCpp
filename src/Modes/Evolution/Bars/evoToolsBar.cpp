#include "evoToolsBar.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


void EvoToolsBar::menuControllSelect()
{
    if (currentChoice == toolsBarChoicesConst::Save){
    } else if (currentChoice == toolsBarChoicesConst::Load){
    } else if (currentChoice == toolsBarChoicesConst::Pause){
    } else if (currentChoice == toolsBarChoicesConst::Exit){
        evolutionParameters.gameOn = false;
    }
}


void EvoToolsBar::writeString(int count)
{
    const char *string = toolsBarChoices[count].c_str();
    currentScreen.writeText(string);
}