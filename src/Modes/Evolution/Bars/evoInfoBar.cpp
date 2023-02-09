#include "evoInfoBar.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


EvoInfoBar::EvoInfoBar(int xStart, int yStart, int xEnd, int yEnd) : InfoBar(xStart, yStart, xEnd, yEnd)
{
    barTitle = "~INFORMATION~";

    barChoices = 
    {
        "Gen.",
        "Best Id",
        "Max Food",
        "Alive",
        "Mutations",
        "TurnsToDeath",
        "Time",

        "Best Score",
        "Score",
        "Food",
        "Turns",
        "TurnsLeft",
        "Borders",
        "Speed"
    };

    rows = barChoices.size() / 2;
    columns = barChoices.size() / rows;

    firstBarTitle = Generation;
    lastBarTitle = Speed;
};


int EvoInfoBar::getParameter(int count)
{
    switch(count) {
        case Generation:
            return evolutionParameters.generation;
            break;
        case BestSnakeId:
            return evolutionParameters.bestSnakeId;
            break;
        case MaxFood:
            return evolutionParameters.bestFood;
            break;
        case Score:
            return evolutionParameters.score;
            break;
        case Food:
            return evolutionParameters.countOfFood;
            break;
        case MutChance:
            return evolutionParameters.mutationChance;
            break;
        case BestScore:
            return evolutionParameters.theBestScore;
            break;
        case Alive:
            return evolutionParameters.aliveSnakes;
            break;
        case Time:
            return evolutionParameters.time;
            break;
        case Turn:
            return evolutionParameters.turn;
            break;
        case TurnsLeft:
            return evolutionParameters.hightTurnsLeft;
            break;
        case TurnsToDeath:
            return evolutionParameters.turnsToDeath;
            break;
        case Borders:
            return evolutionParameters.countOfBorders;
            break;
        case Speed:
            return evolutionParameters.delayDuration;
            break;
        default:
            return 0;
    }
}