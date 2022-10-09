#include "evoToolsBar.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


void EvoToolsBar::menuControllSelect()
{
    if (currentChoice == toolsBarChoicesConst::Save){
    } else if (currentChoice == toolsBarChoicesConst::Load){
    } else if (currentChoice == toolsBarChoicesConst::SpeedUp){
        if (evolutionParameters.delayDuration == 1) {
            evolutionParameters.delayDuration = 200;
        } else {
            evolutionParameters.delayDuration--;
        }
        timeout(evolutionParameters.delayDuration);
    } else if (currentChoice == toolsBarChoicesConst::SpeedDown){
        if (evolutionParameters.delayDuration == 200) {
            evolutionParameters.delayDuration = 1;
        } else {
            evolutionParameters.delayDuration++;
        }
        timeout(evolutionParameters.delayDuration);
    } else if (currentChoice == toolsBarChoicesConst::Pause){
        pauseOn = !pauseOn;
    } else if (currentChoice == toolsBarChoicesConst::Exit){
        evolutionParameters.gameOn = false;
    }
}


void EvoToolsBar::writeString(int count)
{
    const char *string = toolsBarChoices[count].c_str();
    currentScreen.writeText(string);
}