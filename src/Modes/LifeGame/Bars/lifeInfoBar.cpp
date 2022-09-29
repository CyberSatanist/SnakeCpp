#include "lifeInfoBar.h"
#include <LifeGame/Parameters/lifeGameParameters.h>

extern LifeGameParameters lifeGameParameters;


int LifeInfoBar::getParameter(int count)
{
    switch(count) {
        case Turn:
            return lifeGameParameters.turn;
            break;
        default:
            return 0;
    }
}


void LifeInfoBar::writeString(int count)
{
    const char *string = infoBarChoices[count].c_str();
    currentScreen.writeText(string);
}