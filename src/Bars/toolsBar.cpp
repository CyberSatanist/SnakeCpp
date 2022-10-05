#include "toolsBar.h"

void ToolsBar::initToolsBar(int xStart, int yStart, int xEnd, int yEnd)
{
    toolsBarXStart = xStart;
    toolsBarYStart = yStart;
    toolsBarXEnd = xEnd;
    toolsBarYEnd = yEnd;
}


void ToolsBar::drawToolsBar()
{
    currentToolsBarTitle = firstToolsBarTitle;
    count = 0;
    for (currentColumn = 1; currentColumn <= columns; currentColumn++) {
        if (count == choicesCount) { break; }
        for (currentRow = 1; currentRow <= rows; currentRow++) {
            currentScreen.setCursor(
                toolsBarXStart + (toolsBarXEnd - toolsBarXStart) / (rows + 1) * currentRow,
                toolsBarYStart + (toolsBarYEnd - toolsBarYStart) / (columns + 1) * currentColumn
            );

            if (currentChoice == count) {
                currentScreen.setColor(COLOR_BLACK, COLOR_WHITE);	
            } else {
                currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);
            }

            writeString(count);
            //const char *string = toolsMenuChoices[count].c_str();
            //currentScreen.writeText(string);

            count++;
            currentToolsBarTitle++;
        }
    }
}


void ToolsBar::menuControllHandler(int key)
{
    switch(key) {
    case currentScreen.controll_keys::UP:
        if (currentChoice == 0) {
            currentChoice = choicesCount - 1;
        } else {
            currentChoice--;
        }
        break;
    case currentScreen.controll_keys::DOWN:
        if (currentChoice == choicesCount - 1) {
            currentChoice = 0;
        } else {
            currentChoice++;
        }
        break;
    case currentScreen.controll_keys::RIGHT:
        if ((currentChoice + rows) > (choicesCount -1)) {
            currentChoice = 0 + (currentChoice % rows);
        } else {
            currentChoice += rows;
        }
        break;
    case currentScreen.controll_keys::LEFT:
        if ((currentChoice - rows) < 0) {
            currentChoice = choicesCount + (currentChoice - rows);
        } else {
            currentChoice -= rows;
        }
        break;
    case currentScreen.controll_keys::SELECT:
        menuControllSelect();
        break;
    }
}

/*
void ToolsSubMenu::menuControllSelect()
{
    if (currentChoice == toolsMenuChoicesConst::Save){
    } else if (currentChoice == toolsMenuChoicesConst::Load){
    } else if (currentChoice == toolsMenuChoicesConst::Pause){
    } else if (currentChoice == toolsMenuChoicesConst::Exit){
        evolutionParameters.gameOn = false;
    }
}
*/