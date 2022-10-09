#include "evoInfoBar.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


int EvoInfoBar::getParameter(int count)
{
    switch(count) {
        case Generation:
            return evolutionParameters.generation;
            break;
        case BestSnakeId:
            return evolutionParameters.bestSnakeId;
            break;
        case Score:
            return evolutionParameters.score;
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
        case Speed:
            return evolutionParameters.delayDuration;
            break;
        default:
            return 0;
    }
}

void EvoInfoBar::writeString(int count)
{
    const char *string = infoBarChoices[count].c_str();
    currentScreen.writeText(string);
}