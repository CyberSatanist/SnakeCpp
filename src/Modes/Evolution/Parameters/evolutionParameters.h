#ifndef EVOLUTION_PARAMETERS_H
#define EVOLUTION_PARAMETERS_H

#include "../../../Screen/screen.h"

class EvolutionParameters 
{
    public:
        bool evolutionOn = false;
        int delayDuration = 5;

//Field-ToolsMenu
        int fieldX = 3;
        int fieldMaxX = 4;
        int fieldY = 5;
        int fieldMaxY = 6;

//Statistic info
        int generation = 0;
        int score = 0;
        int time = 0;

};

#endif
