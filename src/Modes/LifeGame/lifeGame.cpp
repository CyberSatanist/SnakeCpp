#include "lifeGame.h"


void LifeGame::run()
{
    timeout(lifeGameParameters.delayDuration);

    currentScreen.clearScreen();

    lifeGameParameters.turn = 0;

	lifeGameParameters.gameOn = true;

    while(lifeGameParameters.gameOn){
        key = currentScreen.controllHandler();
        turn();
        drawScreen();
        if (lifeGameParameters.moveField){
            field.moveHandler(key);
        } else if (lifeGameParameters.drawCells){
            field.drawCellsHandler(key);
        } else {
            toolsBar.menuControllHandler(key);
        }

    }
    currentScreen.clearScreen();
}


void LifeGame::turn()
{
    if (lifeGameParameters.reset){
        lifeGameParameters.reset = false;
        field.reset();
    } else if (lifeGameParameters.clean){
        lifeGameParameters.clean = false;
        field.clean();
    } else if (!lifeGameParameters.pauseOn) {
        field.makeTurn();
        lifeGameParameters.turn++;
    }
}


void LifeGame::drawScreen()
{
    field.drawField();
    infoBar.drawBar();
    toolsBar.drawBar();
    squareBar.drawMap(field);
    currentScreen.endFrame();
}
