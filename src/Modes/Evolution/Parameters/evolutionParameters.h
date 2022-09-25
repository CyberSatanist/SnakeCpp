#ifndef EVOLUTION_PARAMETERS_H
#define EVOLUTION_PARAMETERS_H

class EvolutionParameters 
{
    public:
        bool evolutionOn = false;
        int delayDuration = 80;
        int whiteColor = COLOR_WHITE;

//Field-ToolsMenu
        int fieldX = 3;
        int fieldMaxX = 4;
        int fieldY = 5;
        int fieldMaxY = 6;

//Statistic info
        int generation = 0;
        int score = 0;
        int time = 0;
        int turn = 0;

//SnakeParameters
        int countOfSnakes = 1;
        int snakeLength = 6;
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

};

#endif
