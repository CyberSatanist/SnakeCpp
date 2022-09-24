#include "infoSubMenu.h"
#include "../../Parameters/evolutionParameters.h"

extern EvolutionParameters evolutionParameters;

void InfoSubMenu::initInfoBar(int xStart, int yStart, int xEnd, int yEnd)
{
    infoBarXStart = xStart;
    infoBarYStart = yStart;
    infoBarXEnd = xEnd;
    infoBarYEnd = yEnd;
}


void InfoSubMenu::drawInfoBar()
{
    for (
        int count = 0, currentInfoMenuTitle = firstInfoMenuTitle;
        count < infoMenuChoiceCount; 
        count++, currentInfoMenuTitle++
    ) {
        currentScreen.setCursor(
            infoBarXEnd / (infoMenuChoiceCount + 1) * (count+1),
            infoBarYStart + (infoBarYEnd - infoBarYStart - infoMenuChoices[count].length())/2
        );
        currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);       
        const char *string = infoMenuChoices[count].c_str();
        currentScreen.writeText(string);

        currentScreen.setCursor(
            (infoBarXEnd / (infoMenuChoiceCount + 1) * (count+1)) + 2,
            infoBarYStart - 1 + (infoBarYEnd - infoBarYStart)/2
        );

        currentInfoParameter = getParameter(currentInfoMenuTitle);
        printParameter(currentInfoParameter);
    }
}


int InfoSubMenu::getParameter(int count)
{
    switch(count) {
        case Generation:
            return evolutionParameters.generation;
            break;
        case Score:
            return evolutionParameters.score;
            break;
        case Time:
            return evolutionParameters.time;
            break;
        default:
            return 0;
    }
}


void InfoSubMenu::printParameter(int parameter)
{
    std::string parameterString;
    parameterString = std::to_string(parameter);
    const char *parameterChar = parameterString.c_str();
	currentScreen.writeText(parameterChar);
}