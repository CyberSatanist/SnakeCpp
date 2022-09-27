#include "lifeGame.h"
#include "Parameters/lifeGameParameters.h"

extern LifeGameParameters lifeGameParameters;

LifeGame::LifeGame()
{
    infoSubMenu.initInfoBar(
        0,
        currentScreen.getWidth() / lifeGameParameters.fieldMaxY * lifeGameParameters.fieldY + 1,
        currentScreen.getHight() / lifeGameParameters.fieldMaxX * lifeGameParameters.fieldX,
        currentScreen.getWidth()
    );

    toolsSubMenu.initToolsBar(
        currentScreen.getHight() / lifeGameParameters.fieldMaxX * lifeGameParameters.fieldX + 1, 
        0, 
        currentScreen.getHight(), 
        currentScreen.getWidth()
    );

    map.initMap(
        currentScreen.getHight() / lifeGameParameters.fieldMaxX * lifeGameParameters.fieldX,
        currentScreen.getWidth() / lifeGameParameters.fieldMaxY * lifeGameParameters.fieldY
    );

    timeout(lifeGameParameters.delayDuration);
}


void LifeGame::run()
{
    currentScreen.clearScreen();

    lifeGameParameters.turn = 0;

	lifeGameParameters.lifeGameOn = true;

    while((key = currentScreen.controllHandler()) !=-1  & (lifeGameParameters.lifeGameOn)){
        turn();
        drawScreen();
        toolsSubMenu.menuControllHandler(key);

        lifeGameParameters.turn++;
    }
    currentScreen.clearScreen();
}


void LifeGame::turn()
{

}


void LifeGame::drawScreen()
{
    map.drawField();
    infoSubMenu.drawInfoBar();
    toolsSubMenu.drawToolsBar();
    currentScreen.endFrame();
}
