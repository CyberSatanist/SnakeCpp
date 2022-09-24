#include "evolution.h"
#include "Parameters/evolutionParameters.h"
#include "Field/map.h"
#include <ncurses.h>
#include <unistd.h>

extern EvolutionParameters evolutionParameters;

Evolution::Evolution(Screen screen)
{
    Screen currentScreen;

    infoBarXStart = 0;
    infoBarYStart = currentScreen.getWidth() /  evolutionParameters.fieldMaxY * evolutionParameters.fieldY + 1;
    infoBarXEnd = currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX;
    infoBarYEnd = currentScreen.getWidth();

    toolBarXStart = currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX + 1;
    toolBarYStart = 0;
    toolBarXEnd = currentScreen.getHight();
    toolBarYEnd = currentScreen.getWidth();

    map.initMap(
        currentScreen.getHight() / evolutionParameters.fieldMaxX * evolutionParameters.fieldX,
        currentScreen.getWidth() /  evolutionParameters.fieldMaxY * evolutionParameters.fieldY
    );

    timeout(evolutionParameters.delayDuration);
}

void Evolution::run()
{
	evolutionParameters.evolutionOn = true;

    while((key = currentScreen.controllHandler()) !=-1  & (evolutionParameters.evolutionOn)){
        turn();
        drawScreen();
        menuControllHandler();
        if (key == Screen::controll_keys::ESCAPE) {
            evolutionParameters.evolutionOn = false;
        }
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
    drawField();
    drawInfoBar();
    drawToolsBar();
    currentScreen.endFrame();
}

void Evolution::drawField()
{
    for(int countX = 0; countX < map.getSizeX(); countX++){
        for(int countY = 0; countY < map.getSizeY(); countY++){
            if(map.getCell(countX, countY) == Map::Free){
                currentScreen.setColor(COLOR_WHITE, COLOR_WHITE);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (map.getCell(countX, countY) == Map::Wall){
                currentScreen.setColor(COLOR_BLUE, COLOR_BLUE);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (map.getCell(countX, countY) == Map::Snake){
                currentScreen.setColor(COLOR_GREEN, COLOR_GREEN);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            } else if (map.getCell(countX, countY) == Map::Food){
                currentScreen.setColor(COLOR_RED, COLOR_RED);
                currentScreen.setCursor(countX, countY);
                currentScreen.writeText(" ");
            }
        }
    }
}

void Evolution::drawInfoBar()
{
    for (
        int count = 0, currentInfoMenuTitle = firstInfoMenuTitle;
        count < infoMenuChoiceCount; 
        count++, currentInfoMenuTitle++
    ) {
        currentScreen.setCursor(
            infoBarXEnd / (infoMenuChoiceCount + 1) * (count+1),
            infoBarYStart + (infoBarYEnd - infoBarYStart - infoMenuChoices[count].length())/2
        );
        currentScreen.setColor(COLOR_WHITE, COLOR_BLACK);       
        const char *string = infoMenuChoices[count].c_str();
        currentScreen.writeText(string);

        currentScreen.setCursor(
            (infoBarXEnd / (infoMenuChoiceCount + 1) * (count+1)) + 2,
            infoBarYStart - 1 + (infoBarYEnd - infoBarYStart)/2
        );

        currentInfoParameter = getParameter(currentInfoMenuTitle);
        printParameter(currentInfoParameter);
    }
}

void Evolution::drawToolsBar()
{
    currentToolsMenuTitle = firstToolsMenuTitle;
    count = 0;
    for (currentColumn = 1; currentColumn <= columns; currentColumn++) {
        if (count == toolsMenuChoiceCount) { break; }
        for (currentRow = 1; currentRow <= rows; currentRow++) {
            currentScreen.setCursor(
                toolBarXStart + (toolBarXEnd - toolBarXStart) / (rows + 1) * currentRow,
                toolBarYStart + (toolBarYEnd - toolBarYStart) / (columns + 1) * currentColumn
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


int Evolution::getParameter(int count)
{
    switch(count) {
        case Generation:
            return generation;
            break;
        case Score:
            return score;
            break;
        case Time:
            return time;
            break;
        default:
            return 0;
    }
}

void Evolution::printParameter(int parameter)
{
    std::string parameterString;
    parameterString = std::to_string(parameter);
    const char *parameterChar = parameterString.c_str();
	currentScreen.writeText(parameterChar);
}

void Evolution::menuControllHandler()
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


void Evolution::menuControllSelect()
{
    if (currentChoice == toolsMenuChoicesConst::Save){
    } else if (currentChoice == toolsMenuChoicesConst::Load){
    } else if (currentChoice == toolsMenuChoicesConst::Pause){
    } else if (currentChoice == toolsMenuChoicesConst::Exit){
        evolutionParameters.evolutionOn = false;
    }
}