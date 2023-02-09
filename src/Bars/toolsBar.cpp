#include "toolsBar.h"


void ToolsBar::drawBar()
{
    int currentBarTitle = firstBarTitle;
    int count = 0;

    drawBorders();

    for (currentColumn = 1; currentColumn <= columns; currentColumn++) {
        if (count == (int) barChoices.size()) { break; }
        for (currentRow = 1; currentRow <= rows; currentRow++) {
            currentScreen.setCursor(
                startX + (endX - startX) / (rows + 1) * currentRow,
                startY + (endY - startY) / (columns + 1) * currentColumn
            );

            if (currentChoice == count) {
                currentScreen.setColor(COLOR_BLACK, COLOR_YELLOW);	
            } else {
                currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);
            }

            writeString(count);

            count++;
            currentBarTitle++;
        }
    }
}


void ToolsBar::menuControllHandler(int key)
{
    switch(key) {
    case currentScreen.controll_keys::UP:
        if (currentChoice == 0) {
            currentChoice = (int) barChoices.size() - 1;
        } else {
            currentChoice--;
        }
        break;
    case currentScreen.controll_keys::DOWN:
        if (currentChoice == (int) barChoices.size() - 1) {
            currentChoice = 0;
        } else {
            currentChoice++;
        }
        break;
    case currentScreen.controll_keys::RIGHT:
        if ((currentChoice + rows) > ((int) barChoices.size() -1)) {
            currentChoice = 0 + (currentChoice % rows);
        } else {
            currentChoice += rows;
        }
        break;
    case currentScreen.controll_keys::LEFT:
        if ((currentChoice - rows) < 0) {
            currentChoice = (int) barChoices.size() + (currentChoice - rows);
        } else {
            currentChoice -= rows;
        }
        break;
    case currentScreen.controll_keys::SELECT:
        menuControllSelect();
        break;
    }
}