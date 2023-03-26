#ifndef EVOLUTION_PARAMETERS_H
#define EVOLUTION_PARAMETERS_H

#include "Parameters/parameters.h"

class EvolutionParameters : public Parameters
{
    public:
        int delayDuration = 10;

//Statistic info
        int generation = 1;
        int score = 0;
        int theBestScore = 0;
        int aliveSnakes = 0;
        int time = 0;
        int turn = 0;
        int bestSnakeId = 0;
        int bestFood = 0;
        int snakeIdCounter = 1;
        int turnsToDeath = 500;
        int hightTurnsLeft = turnsToDeath;

//SnakeParameters
        int countOfSnakes = 100;
        int snakeLength = 2;
        int snakeHeadColor = COLOR_YELLOW;
        int snakeOneBodyColor = COLOR_GREEN;
        int snakeTwoBodyColor = COLOR_BLACK;
        int snakeThreeBodyColor = COLOR_GREEN;
        int snakeFourBodyColor = COLOR_GREEN;
        int snakeFiveBodyColor = COLOR_GREEN;

//FoodModel
        int countOfFood = 10;
        int snakeOnefoodColor = COLOR_RED;
        int snakeTwofoodColor = COLOR_RED;
        int snakeThreefoodColor = COLOR_RED;
        int snakeFourfoodColor = COLOR_RED;
        int snakeFivefoodColor = COLOR_RED;

//Borders
        int countOfBorders = 0;

//Cell Colors
        int freeCellColor = COLOR_WHITE;
        int wallCellColor = COLOR_BLUE;
        int snakeCellColor = COLOR_GREEN;
        int foodCellColor = COLOR_RED;

//Neural Network
        enum networkTypes{StandartNetworkType, StraightNetworkType, SimpleNetworkType};
        int currentNetwork = SimpleNetworkType;

        int inputLayerNeuronCount = 81;
        int countOfHiddenLayers = 2;
        int hiddenLayerNeuronCount = 5;
        int outputLayerNeuronCount = 4;

//Generetions
        int countOfBest = 30;
        int countOfWorst = 2;
        int mutationChance = 2;
};

#endif
