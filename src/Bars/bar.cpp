#include "bar.h"


void Bar::drawBorders()
{
    for (int x = startX; x < endX; x++){
        currentScreen.setCursor(x, startY);
        currentScreen.setColor(COLOR_YELLOW, COLOR_YELLOW);
        currentScreen.writeText(" ");
        currentScreen.setCursor(x, endY - 1);
        currentScreen.setColor(COLOR_YELLOW, COLOR_YELLOW);
        currentScreen.writeText(" ");
    }

    for (int y = startY; y < endY; y++){
        currentScreen.setCursor(startX, y);
        currentScreen.setColor(COLOR_YELLOW, COLOR_YELLOW);
        currentScreen.writeText(" ");
        currentScreen.setCursor(endX - 1, y);
        currentScreen.setColor(COLOR_YELLOW, COLOR_YELLOW);
        currentScreen.writeText(" ");
    }
}


void Bar::printParameter(int parameter)
{
	currentScreen.writeText(std::to_string(parameter).c_str());
}



void Bar::writeString(int count)
{
    currentScreen.writeText(barChoices.at(count).c_str());
}