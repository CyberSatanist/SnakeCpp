#include "toolsBar.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;

void ToolsSubMenu::initToolsBar(int xStart, int yStart, int xEnd, int yEnd)
{
    toolsBarXStart = xStart;
    toolsBarYStart = yStart;
    toolsBarXEnd = xEnd;
    toolsBarYEnd = yEnd;
}


void ToolsSubMenu::drawToolsBar()
{
    currentToolsMenuTitle = firstToolsMenuTitle;
    count = 0;
    for (currentColumn = 1; currentColumn <= columns; currentColumn++) {
        if (count == toolsMenuChoiceCount) { break; }
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

            const char *string = toolsMenuChoices[count].c_str();
            currentScreen.writeText(string);

            count++;
            currentToolsMenuTitle++;
        }
    }
}


void ToolsSubMenu::menuControllHandler(int key)
{
    switch(key) {
    case currentScreen.controll_keys::UP:
        if (currentChoice == 0) {
            currentChoice = toolsMenuChoiceCount - 1;
        } else {
            currentChoice--;
        }
        break;
    case currentScreen.controll_keys::DOWN:
        if (currentChoice == toolsMenuChoiceCount - 1) {
            currentChoice = 0;
        } else {
            currentChoice++;
        }
        break;
    case currentScreen.controll_keys::RIGHT:
        if ((currentChoice + rows) > (toolsMenuChoiceCount -1)) {
            currentChoice = 0 + (currentChoice % rows);
        } else {
            currentChoice += rows;
        }
        break;
    case currentScreen.controll_keys::LEFT:
        if ((currentChoice - rows) < 0) {
            currentChoice = toolsMenuChoiceCount + (currentChoice - rows);
        } else {
            currentChoice -= rows;
        }
        break;
    case currentScreen.controll_keys::SELECT:
        menuControllSelect();
        break;
    }
}


void ToolsSubMenu::menuControllSelect()
{
    if (currentChoice == toolsMenuChoicesConst::Save){
    } else if (currentChoice == toolsMenuChoicesConst::Load){
    } else if (currentChoice == toolsMenuChoicesConst::Pause){
    } else if (currentChoice == toolsMenuChoicesConst::Exit){
        evolutionParameters.gameOn = false;
    }
}