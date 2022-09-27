#include "lifeInfoSubMenu.h"
#include "../../Parameters/lifeGameParameters.h"

extern LifeGameParameters lifeGameParameters;

void LifeInfoSubMenu::initInfoBar(int xStart, int yStart, int xEnd, int yEnd)
{
    infoBarXStart = xStart;
    infoBarYStart = yStart;
    infoBarXEnd = xEnd;
    infoBarYEnd = yEnd;
}


void LifeInfoSubMenu::drawInfoBar()
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


int LifeInfoSubMenu::getParameter(int count)
{
    switch(count) {
        case Turn:
            return lifeGameParameters.turn;
            break;
        case FieldX:
            return lifeGameParameters.MapSizeX;
            break;
        case FieldY:
            return lifeGameParameters.MapSizeY;
            break;
        case StartX:
            return lifeGameParameters.currentStartX;
            break;
        case StartY:
            return lifeGameParameters.currentStartY;
            break;
        case EndX:
            return lifeGameParameters.currentEndX;
            break;
        case EndY:
            return lifeGameParameters.currentEndY;
            break;
        default:
            return 0;
    }
}


void LifeInfoSubMenu::printParameter(int parameter)
{
    std::string parameterString;
    parameterString = std::to_string(parameter);
    const char *parameterChar = parameterString.c_str();
	currentScreen.writeText(parameterChar);
}