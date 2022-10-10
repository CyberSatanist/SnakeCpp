#ifndef EVOLUTION_PARAMETERS_H
#define EVOLUTION_PARAMETERS_H

#include <Parameters/parameters.h>

class EvolutionParameters : public Parameters
{
    public:
        int delayDuration = 200;

//Statistic info
        int generation = 1;
        int score = 0;
        int theBestScore = 0;
        int aliveSnakes = 0;
        int time = 0;
        int turn = 0;
        int bestSnakeId = 0;
        int snakeIdCounter = 1;

//SnakeParameters
        int countOfSnakes = 40;
        int snakeLength = 1;
        int snakeHeadColor = COLOR_YELLOW;
        int snakeOneBodyColor = COLOR_GREEN;
        int snakeTwoBodyColor = COLOR_BLACK;
        int snakeThreeBodyColor = COLOR_GREEN;
        int snakeFourBodyColor = COLOR_GREEN;
        int snakeFiveBodyColor = COLOR_GREEN;

//FoodModel
        int countOfFood = 1;
        int snakeOnefoodColor = COLOR_RED;
        int snakeTwofoodColor = COLOR_RED;
        int snakeThreefoodColor = COLOR_RED;
        int snakeFourfoodColor = COLOR_RED;
        int snakeFivefoodColor = COLOR_RED;

//Cell Colors
        int freeCellColor = COLOR_WHITE;
        int wallCellColor = COLOR_BLUE;
        int snakeCellColor = COLOR_GREEN;
        int foodCellColor = COLOR_RED;

//Neural Network
        int countOfLayers = 2;
        int countOfNeuronsInLayer = 100;
        int neuronIdCounter = 1;
        int layerIdCounter = 1;

        int firstLayerNeuronCount = 81;
        int lastLayerNeuronCount = 4;
        int outputLayerNeuronCount = 1;

//Generetions
        int countOfBest = 30;
        int countOfWorst = 6;
        int mutationChance = 10;
};

#endif
