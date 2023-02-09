#include "infoBar.h"

extern Screen currentScreen;


void InfoBar::drawBar()
{
    int currentBarTitle = firstBarTitle;
    int count = 0;

    drawBorders();
    
    for (int currentColumn = 1; currentColumn <= columns; currentColumn++) {
        for (int currentRow = 1; currentRow <= rows; currentRow++) {
             currentScreen.setCursor(
                startX + (endX - startX) / (rows + 1) * currentRow,
                startY + (endY - startY) / (columns + 3) * currentColumn * 2 - currentColumn * 2
            );
            
            currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);
            writeString(count);

            currentScreen.setCursor(
                1 + startX + (endX - startX) / (rows + 1) * currentRow,
                startY + (endY - startY) / (columns + 3) * currentColumn * 2 - currentColumn * 2
            );
            printParameter(getParameter(currentBarTitle));
            currentBarTitle++;
            count++;
        }
    }
}