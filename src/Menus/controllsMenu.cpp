#include "controllsMenu.h"
#include "../Screen/screen.h"

void ControllsMenu::run()
{
    controllsMenuOn = true;
    currentScreen.clearScreen();
    while (controllsMenuOn) {
        menuFrame();
        menuControllHandler();
    }
    currentScreen.clearScreen();
}

void ControllsMenu::menuFrame()
{
    for (int count = 0; count < ((controllsMenuChoiceCount - 1) / 2); count++) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / ((controllsMenuChoiceCount-1))) * (count+2)),
            (currentScreen.getWidth() / 7));
        const char *strings = controllsMenuChoices[count].c_str();
        currentScreen.writeText(strings);
    }
    for (int count = ((controllsMenuChoiceCount - 1) / 2), line = 0; count < controllsMenuChoiceCount - 1; count++, line++) {
        currentScreen.setCursor(
            ((currentScreen.getHight() / ((controllsMenuChoiceCount - 1))) * (line+2)),
            (currentScreen.getWidth() / 7) * 4);
        const char *strings = controllsMenuChoices[count].c_str();
        currentScreen.writeText(strings);
    }
    currentScreen.setCursor(
        currentScreen.getHight() - controllsMenuChoiceCount,
        (currentScreen.getWidth() - controllsMenuChoices[controllsMenuChoiceCount -1].length()) / 2 
    );
    const char *strings = controllsMenuChoices[controllsMenuChoiceCount - 1].c_str();
    setMenuChosenColor();	
    currentScreen.writeText(strings);
    currentScreen.endFrame();
    setMenuLineColor();
}

void ControllsMenu::menuControllHandler()
{
    switch (currentScreen.controllHandler()) { 
        case currentScreen.controll_keys::SELECT:
        case currentScreen.controll_keys::ESCAPE:
           controllsMenuOn = false;
        break;
    }
}
