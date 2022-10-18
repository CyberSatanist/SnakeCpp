#ifndef EVOLUTION_PARAMETERS_H
#define EVOLUTION_PARAMETERS_H

#include <Parameters/parameters.h>

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
        int snakeIdCounter = 1;
        int turnsToDeath = 300;

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
        int countOfLayers = 0;
        int countOfNeuronsInLayer = 0;
        int neuronIdCounter = 1;
        int layerIdCounter = 1;

        int firstLayerNeuronCount = 25;
        int lastLayerNeuronCount = 4;
        int outputLayerNeuronCount = 1;

//Generetions
        int countOfBest = 10;
        int countOfWorst = 0;
        int mutationChance = 2;
};

#endif
