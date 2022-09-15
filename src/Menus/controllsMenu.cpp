#include "controllsMenu.h"
#include "../Screen/screen.h"


/*void ControllsMenu::menuFrame()
{
    for (int count = 0; count < ((menuChoiceCount - 1) / 2); count++) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / ((menuChoiceCount-1))) * (count+2)),
            (currentScreen.getWidth() / 7));
        const char *string = menuChoices[count].c_str();
        currentScreen.writeText(string);
    }
    for (int count = ((menuChoiceCount - 1) / 2), line = 0; count < menuChoiceCount - 1; count++, line++) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / ((menuChoiceCount - 1))) * (line+2)),
            (currentScreen.getWidth() / 7) * 4);
        const char *strings = menuChoices[count].c_str();
        currentScreen.writeText(strings);
    }
    currentScreen.setCursor(
        currentScreen.getHight() - menuChoiceCount,
        (currentScreen.getWidth() - menuChoices[menuChoiceCount -1].length()) / 2 
    );
    const char *strings = menuChoices[menuChoiceCount - 1].c_str();
    setMenuChosenColor();	
    currentScreen.writeText(strings);
    currentScreen.endFrame();
    setMenuLineColor();
}*/


void ControllsMenu::menuControllSelect()
{
    menuOn = false;
}