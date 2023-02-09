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
        toolsBar.menuControllHandler(key);

        lifeGameParameters.turn++;
    }
    currentScreen.clearScreen();
}


void LifeGame::turn()
{

}


void LifeGame::drawScreen()
{
    field.drawField();
    infoBar.drawBar();
    toolsBar.drawBar();
    currentScreen.endFrame();
}
