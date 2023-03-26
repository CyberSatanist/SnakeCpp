#include "evoToolsBar.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


EvoToolsBar::EvoToolsBar(int xStart, int yStart, int xEnd, int yEnd) : ToolsBar(xStart, yStart, xEnd, yEnd)
{
    barTitle = "~TOOLS~";

    barChoices = 
    {
        "Speed++",
        "Speed--",
        "Food++",
        "Food--",
        "Mutation++",
        "Mutation--",
        "TurnsToDeath++",
        "TurnsToDeath--",
        "Borders++",
        "Borders--",
        "Pause",
        "Exit",
    };

    rows = barChoices.size() / 5;
    columns = barChoices.size() / rows;

    firstBarTitle = SpeedUp;
    lastBarTitle = Exit;
}


void EvoToolsBar::menuControllSelect()
{
    if (currentChoice == barChoicesConst::SpeedUp){
        if (evolutionParameters.delayDuration == 1) {
            evolutionParameters.delayDuration = 200;
        } else {
            evolutionParameters.delayDuration--;
        }
        timeout(evolutionParameters.delayDuration);
    } else if (currentChoice == barChoicesConst::SpeedDown){
        if (evolutionParameters.delayDuration == 200) {
            evolutionParameters.delayDuration = 1;
        } else {
            evolutionParameters.delayDuration++;
        }
        timeout(evolutionParameters.delayDuration);
    } else if (currentChoice == barChoicesConst::FoodUp){
        if (evolutionParameters.countOfFood == 200) {
            evolutionParameters.countOfFood = 0;
        } else {
            evolutionParameters.countOfFood++;
        }
    } else if (currentChoice == barChoicesConst::FoodDown){
        if (evolutionParameters.countOfFood == 0) {
            evolutionParameters.countOfFood = 200;
        } else {
            evolutionParameters.countOfFood--;
        }
    } else if (currentChoice == barChoicesConst::MutPlus){
        if (evolutionParameters.mutationChance == 100) {
            evolutionParameters.mutationChance = 0;
        } else {
            evolutionParameters.mutationChance += 2;
        }
    } else if (currentChoice == barChoicesConst::MutMinus){
        if (evolutionParameters.mutationChance == 0) {
            evolutionParameters.mutationChance = 100;
        } else {
            evolutionParameters.mutationChance -= 2;
        }
    } else if (currentChoice == barChoicesConst::TurnsToDeathUp){
        if (evolutionParameters.turnsToDeath == 1000) {
            evolutionParameters.turnsToDeath = 0;
        } else {
            evolutionParameters.turnsToDeath += 10;
        }
    } else if (currentChoice == barChoicesConst::TurnsToDeathDown){
        if (evolutionParameters.turnsToDeath == 0) {
            evolutionParameters.turnsToDeath = 1000;
        } else {
            evolutionParameters.turnsToDeath -= 10;
        }
    } else if (currentChoice == barChoicesConst::BordersUp){
        if (evolutionParameters.countOfBorders == 200) {
            evolutionParameters.countOfBorders = 0;
        } else {
            evolutionParameters.countOfBorders++;
        }
    } else if (currentChoice == barChoicesConst::BordersDown){
        if (evolutionParameters.countOfBorders == 0) {
            evolutionParameters.countOfBorders = 200;
        } else {
            evolutionParameters.countOfBorders--;
        }
    } else if (currentChoice == barChoicesConst::Pause){
        pauseOn = !pauseOn;
    } else if (currentChoice == barChoicesConst::Exit){
        evolutionParameters.gameOn = false;
    }
}