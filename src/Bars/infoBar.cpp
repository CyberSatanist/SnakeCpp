#include "infoBar.h"

void InfoBar::initInfoBar(int xStart, int yStart, int xEnd, int yEnd)
{
    infoBarXStart = xStart;
    infoBarYStart = yStart;
    infoBarXEnd = xEnd;
    infoBarYEnd = yEnd;
}


void InfoBar::drawInfoBar()
{
    currentInfoBarTitle = firstInfoBarTitle;
    count = 0;

   for (int currentColumn = 1; currentColumn <= columns; currentColumn++) {
        for (int currentRow = 1; currentRow <= rows; currentRow++) {
             currentScreen.setCursor(
                infoBarXStart + (infoBarXEnd - infoBarXStart) / (rows + 1) * currentRow,
                infoBarYStart + (infoBarYEnd - infoBarYStart) / (columns + 1) * currentColumn
            );
            
            currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);
            writeString(count);

            currentScreen.setCursor(
                1 + infoBarXStart + (infoBarXEnd - infoBarXStart) / (rows + 1) * currentRow,
                infoBarYStart + (infoBarYEnd - infoBarYStart) / (columns + 1) * currentColumn
            );
            currentInfoParameter = getParameter(currentInfoBarTitle);
            printParameter(currentInfoParameter);
            currentInfoBarTitle++;
            count++;
        }
    }
    /*
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
    }*/
}


void InfoBar::printParameter(int parameter)
{
    std::string parameterString;
    parameterString = std::to_string(parameter);
    const char *parameterChar = parameterString.c_str();
	currentScreen.writeText(parameterChar);
}