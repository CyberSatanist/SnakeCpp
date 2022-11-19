#include "lifeGame.h"
#include <LifeGame/Parameters/lifeGameParameters.h>

extern LifeGameParameters lifeGameParameters;

LifeGame::LifeGame()
{
    infoBar.initInfoBar(
        lifeGameParameters.infoBarStartX,
        lifeGameParameters.infoBarStartY,
        lifeGameParameters.infoBarEndX,
        lifeGameParameters.infoBarEndY
    );
    toolsBar.initToolsBar(
        lifeGameParameters.toolsBarStartX,
        lifeGameParameters.toolsBarStartY, 
        lifeGameParameters.toolsBarEndX, 
        lifeGameParameters.toolsBarEndY
    );
    field.initField(
        lifeGameParameters.currentFieldSizeX,
        lifeGameParameters.currentFieldSizeY,
        lifeGameParameters.fullFieldSizeX,
        lifeGameParameters.fullFieldSizeY
    );   

}


LifeGame::~LifeGame()
{
    field.deleteField();
}


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
    infoBar.drawInfoBar();
    toolsBar.drawToolsBar();
    currentScreen.endFrame();
}
