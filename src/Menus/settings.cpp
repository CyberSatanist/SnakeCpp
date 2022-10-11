#include "settings.h"

void Settings::run()
{
    currentScreen.clearScreen();
    settingsOn = true;
    while (settingsOn) {
        this->menuFrame();
        this->menuControllHandler();
    }
    currentScreen.clearScreen();
}


void Settings::menuFrame()
{
    int count = 0;
    currentMenuTitle = firstMenuTitle;
    for (int currentColumn = 1; currentColumn <= columns; currentColumn++) {
        for (int currentRow = 1; currentRow <= rows; currentRow++) {
            currentScreen.setCursor(
                currentScreen.getHight() / (rows + 1) * currentRow,
                currentScreen.getWidth() / (columns + 1) * currentColumn - columns * rows * 2
            );
            if (currentChoice == count) {
                setMenuChosenColor();
            } else {
                setMenuLineColor();
            }

            writeString(count);

            if (count > colorsFrom) {
                currentParameter = getParameter(currentMenuTitle);
                printColor(currentParameter);
            } else {
                currentParameter = getParameter(currentMenuTitle);
                printParameter(currentParameter);
            }
            
            currentMenuTitle++;
            count++;
        }
    }

    for (int currentButton = 0; currentButton < buttonsConst; currentButton++){
        currentScreen.setCursor(
            currentScreen.getHight() / (rows + buttonsConst) * (rows + currentButton + 1),
            currentScreen.getWidth() / 2
        );
        if (currentChoice == (menuConst + buttonsConst - 1)) {
            setMenuChosenColor();
        } else {
            setMenuLineColor();
        }
        writeButton(currentButton);
    }
    currentScreen.endFrame();
}


void Settings::menuControllHandler()
{
    switch(currentScreen.controllHandler()) {
        case currentScreen.controll_keys::UP: 
            if (currentChoice == 0) {
                currentChoice = menuConst + buttonsConst - 1;
            } else {
                currentChoice--;
            }
            break;
        case currentScreen.controll_keys::DOWN: 
            if (currentChoice == menuConst + buttonsConst - 1) {
                currentChoice = 0;
            } else {
                currentChoice++;
            }
            break;
        case currentScreen.controll_keys::LEFT:
            setParameter(currentChoice, currentScreen.controll_keys::LEFT);
            break;
        case currentScreen.controll_keys::RIGHT:
            setParameter(currentChoice, currentScreen.controll_keys::RIGHT);
            break;
        case currentScreen.controll_keys::SELECT:
            menuControllSelect();
            break;
        case currentScreen.controll_keys::ESCAPE:
            settingsOn = false;
            break;
        case currentScreen.controll_keys::NOTHING:
            break;
        }
}

void Settings::printParameter(int parameter)
{
    std::string parameterString;
    parameterString = std::to_string(parameter);
    const char *parameterChar = parameterString.c_str();

    currentScreen.writeText(space);
    currentScreen.writeText(leftArrow);
	currentScreen.writeText(parameterChar);
    currentScreen.writeText(rightArrow);
}



void Settings::printColor(int parameter)
{
    std::string parameterString;
    switch (parameter)
    {
        case COLOR_BLACK:
            parameterString = "Black";
            break;
        case COLOR_RED:
            parameterString = "Red";
            break;
        case COLOR_GREEN:
            parameterString = "Green";
            break;
        case COLOR_YELLOW:
            parameterString = "Yellow";
            break;
        case COLOR_BLUE:
            parameterString = "Blue";
            break;
        case COLOR_MAGENTA:
            parameterString = "Magenta";
            break;
        case COLOR_CYAN:
            parameterString = "Cyan";
            break;
        case COLOR_WHITE:
            parameterString = "White";
            break;
    }
    const char *parameterChar = parameterString.c_str();
    
    currentScreen.writeText(space);
    currentScreen.writeText(leftArrow);
	currentScreen.writeText(parameterChar);
    currentScreen.writeText(rightArrow);
}


void Settings::setMenuChosenColor()
{
    currentScreen.setColor(COLOR_BLACK, COLOR_WHITE);
}


void Settings::setMenuLineColor()
{
    currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);
}


void Settings::setMenuTitleColor()
{
    currentScreen.setColor(COLOR_BLACK, COLOR_YELLOW);
}