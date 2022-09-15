#include <string>
#include "../Screen/screen.h"
#include "menu.h"
       

void Menu::initScreen(Screen screen)
{
    currentScreen = screen;	
}

void Menu::menuFrame()
{
    currentScreen.setCursor(
        currentScreen.getHight() / (menuConst) - 6,
        (currentScreen.getWidth() - menuTitle.length()) / 2);
    setMenuTitleColor();
    const char *title = menuTitle.c_str();
    currentScreen.writeText(title);
    currentScreen.endFrame();
    for (int count = 0; count < menuConst; count++) {
      currentScreen.setCursor(
            (currentScreen.getHight() / (menuConst + 2) * (count+2)),
            (currentScreen.getWidth() / 2) - (menuChoices[count].length())/2);

        if (currentChoice == count) {
            setMenuChosenColor();	
        } else {
            setMenuLineColor();
        }
                
        const char *string = menuChoices[count].c_str();
        
        currentScreen.writeText(string);
             }
     /*
        currentScreen.endFrame();
    }*/
}

void Menu::run()
{
    currentScreen.clearScreen();
    menuOn = true;
    while (menuOn) {
        this->menuFrame();
        this->menuControllHandler();
    }
    currentScreen.clearScreen();
}

void Menu::menuControllHandler()
{
    switch(currentScreen.controllHandler()) {
    case currentScreen.controll_keys::UP: 
        if (currentChoice == 0) {
            currentChoice = menuConst - 1;
        } else {
            currentChoice--;
        }
        break;
    case currentScreen.controll_keys::DOWN: 
        if (currentChoice == menuConst -1) {
            currentChoice = 0;
        } else {
            currentChoice++;
        }
        break;
    case currentScreen.controll_keys::SELECT:
        menuControllSelect();
        break;
    }
}

void Menu::setMenuChosenColor()
{
    currentScreen.setColor(COLOR_BLACK, COLOR_WHITE);
};

void Menu::setMenuLineColor()
{
    currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);
};

void Menu::setMenuTitleColor()
{
    currentScreen.setColor(COLOR_BLACK, COLOR_YELLOW);
};