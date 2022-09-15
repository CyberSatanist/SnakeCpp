#include "evolution.h"
#include "Parameters/evolutionParameters.h"
#include "Field/map.h"
#include <ncurses.h>
#include <unistd.h>

extern EvolutionParameters evolutionParameters;

Evolution::Evolution(Screen screen)
{
    Screen currentScreen;
    map.initMap(
        currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX,
        currentScreen.getWidth() /  evolutionParameters.fieldMaxY * evolutionParameters.fieldY
    );
}

void Evolution::run()
{
	evolutionParameters.evolutionOn = true;

    while((key = currentScreen.controllHandler()) !=-1  & (evolutionParameters.evolutionOn)){
        turn();
	    timeout(evolutionParameters.delayDuration);
        drawScreen();
        if (key == Screen::controll_keys::ESCAPE) {
            evolutionParameters.evolutionOn = false;
        }
    }
}

void Evolution::turn()
{
    currentScreen.endFrame();
    currentScreen.clearScreen();
}

void Evolution::drawScreen()
{
    drawField();
    drawToolsMenu();
    currentScreen.endFrame();
     sleep(1);
    currentScreen.clearScreen();
    sleep(1);
}

void Evolution::drawField()
{
    for(int countX = 0; countX < map.getSizeX(); countX++){
        for(int countY = 0; countY < map.getSizeY(); countY++){
            if(map.getCell(countX, countY) == Map::Free){
                currentScreen.setColor(COLOR_WHITE, COLOR_WHITE);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            }
        }
    }
}

void Evolution::drawToolsMenu()
{

}