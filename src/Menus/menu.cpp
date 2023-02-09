#include "menu.h"

void Menu::menuFrame()
{
    //Drawing title
    currentScreen.setCursor(
        currentScreen.getHight() / ((int) menuChoices.size()) - 6,
        (currentScreen.getWidth() - menuTitle.length()) / 2);
    setMenuTitleColor();
    currentScreen.writeText(menuTitle.c_str());
    currentScreen.endFrame();

    //Drawing menu choises
    for (int count = 0; count < (int) menuChoices.size(); count++) {
      currentScreen.setCursor(
            (currentScreen.getHight() / ((int) menuChoices.size() + 2) * (count + 2)),
            (currentScreen.getWidth() / 2) - (menuChoices.at(count).length()) / 2
        );

        if (currentChoice == count) {
            setMenuChosenColor();	
        } else {
            setMenuLineColor();
        }
        
        currentScreen.writeText(menuChoices.at(count).c_str());
    }
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
                currentChoice = (int) menuChoices.size() - 1;
            } else {
                currentChoice--;
            }
            break;
        case currentScreen.controll_keys::DOWN: 
            if (currentChoice == (int) menuChoices.size() -1) {
                currentChoice = 0;
            } else {
                currentChoice++;
            }
            break;
        case currentScreen.controll_keys::SELECT:
            menuControllSelect();
            break;
        case currentScreen.controll_keys::RIGHT:
            break;
        case currentScreen.controll_keys::LEFT:
            break;
        case currentScreen.controll_keys::ESCAPE:
            break;
        case currentScreen.controll_keys::NOTHING:
            break;
    }
}


void Menu::setMenuChosenColor()
{
    currentScreen.setColor(COLOR_BLACK, COLOR_YELLOW);
}


void Menu::setMenuLineColor()
{
    currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);
}


void Menu::setMenuTitleColor()
{
    currentScreen.setColor(COLOR_BLACK, COLOR_YELLOW);
}