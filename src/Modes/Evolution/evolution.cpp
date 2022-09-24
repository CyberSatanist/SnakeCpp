#include "evolution.h"
#include "Parameters/evolutionParameters.h"
#include "Field/map.h"
#include <ncurses.h>
#include <unistd.h>

extern EvolutionParameters evolutionParameters;

Evolution::Evolution(Screen screen)
{
    Screen currentScreen;

    infoSubMenu.initInfoBar(
        0,
        currentScreen.getWidth() / evolutionParameters.fieldMaxY * evolutionParameters.fieldY + 1,
        currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX,
        currentScreen.getWidth()
    );

    toolsSubMenu.initToolsBar(
        currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX + 1, 
        0, 
        currentScreen.getHight(), 
        currentScreen.getWidth()
    );

    map.initMap(
        currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX,
        currentScreen.getWidth() / evolutionParameters.fieldMaxY * evolutionParameters.fieldY
    );

    timeout(evolutionParameters.delayDuration);
}


void Evolution::run()
{
	evolutionParameters.evolutionOn = true;

    while((key = currentScreen.controllHandler()) !=-1  & (evolutionParameters.evolutionOn)){
        turn();
        drawScreen();
        toolsSubMenu.menuControllHandler(key);
    }
    currentScreen.clearScreen();
}


void Evolution::turn()
{
    currentScreen.endFrame();
    currentScreen.clearScreen();
}


void Evolution::drawScreen()
{
    map.drawField();
    infoSubMenu.drawInfoBar();
    toolsSubMenu.drawToolsBar();
    currentScreen.endFrame();
}