#include "evolution.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <fstream>
#include <iostream>

extern EvolutionParameters evolutionParameters;

Evolution::Evolution()
{
    infoBar.initInfoBar(
        evolutionParameters.infoBarStartX,
        evolutionParameters.infoBarStartY,
        evolutionParameters.infoBarEndX,
        evolutionParameters.infoBarEndY
    );
    toolsBar.initToolsBar(
        evolutionParameters.toolsBarStartX,
        evolutionParameters.toolsBarStartY, 
        evolutionParameters.toolsBarEndX, 
        evolutionParameters.toolsBarEndY
    );
    squareBar.initSquareBar(
        evolutionParameters.squareBarStartX,
        evolutionParameters.squareBarStartY, 
        evolutionParameters.squareBarEndX, 
        evolutionParameters.squareBarEndY
    );
}


void Evolution::run()
{
    timeout(evolutionParameters.delayDuration);

    currentScreen.clearScreen();

    evolutionParameters.turn = 0;
    evolutionParameters.score = 0;
    evolutionParameters.generation = 1;
    evolutionParameters.snakeIdCounter = 1;
    evolutionParameters.aliveSnakes = 0;

    initSnakes();

	evolutionParameters.gameOn = true;

    while(evolutionParameters.gameOn){
        key = currentScreen.controllHandler();

        if (!toolsBar.pauseOn){
            turn();
            evolutionParameters.turn++;
            evolutionParameters.time++;
            snakeTmp = snakes;
            while(snakeTmp->nextSnake){
                if (snakeTmp->currentSnake.isAlive)
                {
                    snakeTmp->currentSnake.setVector(key);
                }
                snakeTmp = snakeTmp->nextSnake;
            }
        }

        if (evolutionParameters.aliveSnakes == 0){
            evolutionParameters.generation++;
            evolutionParameters.turn = 0;
            if (evolutionParameters.score > evolutionParameters.theBestScore){
                evolutionParameters.theBestScore = evolutionParameters.score;
            }
            evolutionParameters.score = 0;
            evolveSnakes();
        }

        drawScreen();
        drawStuff();
        toolsBar.menuControllHandler(key);
    }
    currentScreen.clearScreen();
}


void Evolution::turn()
{
    snakeTmp = snakes;
    while(snakeTmp->nextSnake){
        if (snakeTmp->currentSnake.isAlive)
        {
            snakeTmp->currentSnake.score++;
            if (snakeTmp->currentSnake.score > evolutionParameters.score){
                evolutionParameters.score = snakeTmp->currentSnake.score;
                evolutionParameters.bestSnakeId = snakeTmp->currentSnake.snakeId;
            }
            snakeTmp->currentSnake.move();
        }
        snakeTmp = snakeTmp->nextSnake;
    }

    currentScreen.endFrame();
    currentScreen.clearScreen();
}


void Evolution::drawScreen()
{
    infoBar.drawInfoBar();
    toolsBar.drawToolsBar();
    squareBar.drawMap(snakes->currentSnake.field);

    snakeTmp = snakes;
    do {
        if (snakeTmp->currentSnake.isAlive){
            snakeTmp->currentSnake.drawField();
            break;
        }
        snakeTmp = snakeTmp->nextSnake;
    } while (snakeTmp->nextSnake);
}


void Evolution::drawStuff()
{
    snakeTmp = snakes;
    while(snakeTmp->nextSnake){
        if (snakeTmp->currentSnake.isAlive)
        { 
            snakeTmp->currentSnake.drawStuff();
        }
	    snakeTmp = snakeTmp->nextSnake;
   } 
}


void Evolution::initSnakes()
{
    snakeTmp = snakes;

    int counter = 1;
    for (int count = 0; count < evolutionParameters.countOfSnakes; count++)
	{
        SnakeEvoModel newSnake;
        if ((evolutionParameters.fullFieldSizeY / 2) + (count * 2) + counter > (evolutionParameters.fullFieldSizeY - 3)){
            counter = 1;
        }
        newSnake.init(
            evolutionParameters.fullFieldSizeX / 2,
            evolutionParameters.fullFieldSizeY / 2,
            evolutionParameters.snakeLength,
            evolutionParameters.snakeOneBodyColor
        );
        snakeTmp->currentSnake = newSnake;
        snakeTmp->nextSnake = new snakesList;
        snakeTmp = snakeTmp->nextSnake;
        snakeTmp->nextSnake = NULL;
    counter++;
    }
    squareBar.initField(snakes->currentSnake.field);
}


void Evolution::evolveSnakes()
{
    getBest();
    snakes = new snakesList;
    snakeSecondTmp = snakes;

    int counter = 1;
    for (int count = 0; count < evolutionParameters.countOfSnakes; count++)
	{
        SnakeEvoModel newSnake;
        if ((evolutionParameters.fullFieldSizeY / 2) + (count * 2) + counter > (evolutionParameters.fullFieldSizeY - 3)){
            counter = 1;
        }
        newSnake.init(
            evolutionParameters.fullFieldSizeX / 2,
            evolutionParameters.fullFieldSizeY / 2,
            evolutionParameters.snakeLength,
            evolutionParameters.snakeOneBodyColor
        );

        int parentOneNum = 0;
        int parentTwoNum = 0;

        int parentsCount = ((evolutionParameters.countOfSnakes / 10) * evolutionParameters.countOfBest / 10) + ((evolutionParameters.countOfSnakes / 10) * evolutionParameters.countOfWorst / 10);
        
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> randGen(1, parentsCount - 1);

        while (parentOneNum == parentTwoNum) {
            parentOneNum = randGen(generator);
            parentTwoNum = randGen(generator);
        }

        #ifdef LOGS
        std::ofstream test;
        test.open("mergeTests.txt");
        if (test.is_open()){
            test << "TEST" << std::endl;
            #endif 

            snakeListTmp = parentSnakes;
            for (int count = 0; count < parentOneNum; count++){
                #ifdef LOGS
                test << count << std::endl;
                test << parentOneNum << std::endl;
                #endif

                snakeListTmp = snakeListTmp->nextSnake;

                #ifdef LOGS
                test << "PARENT 1 NEURON ID : " << snakeListTmp->currentSnake.network.firstLayer->currentNeuron.neuronId << "\n" << std::endl;
                #endif
            }
            #ifdef LOGS
            test << "PARENT 1 NEURON ID : " << snakeListTmp->currentSnake.network.firstLayer->currentNeuron.neuronId << "\n" << std::endl;
            #endif
            snakeListSecondTmp = parentSnakes;
            for (int count = 0; count < parentTwoNum; count++){
                #ifdef LOGS
                test << count << std::endl;
                test << "PARENT 2 NEURON ID : " << snakeListSecondTmp->currentSnake.network.firstLayer->currentNeuron.neuronId << "\n" << std::endl;
                #endif       

                snakeListSecondTmp = snakeListSecondTmp->nextSnake;
            }
            #ifdef LOGS
            test << "PARENT 2 NEURON ID : " << snakeListSecondTmp->currentSnake.network.firstLayer->currentNeuron.neuronId << "\n" << std::endl;
        }
        test.close();
        #endif
        
        newSnake.network.mergeNetworks(&(snakeListTmp->currentSnake.network), &(snakeListSecondTmp->currentSnake.network));
        
        snakeSecondTmp->currentSnake = newSnake;
        snakeSecondTmp->nextSnake = new snakesList;
        snakeSecondTmp = snakeSecondTmp->nextSnake;
        snakeSecondTmp->nextSnake = NULL;
        counter++;
    }
    squareBar.initField(snakes->currentSnake.field);
}


void Evolution::getBest()
{
    #ifdef LOGS
    std::ofstream test;
    test.open("bestList.txt");
    #endif

    snakeTmp = snakes;
    bestSnake = new bestSnakesList;
    bestSnake->currentSnake = snakes->currentSnake;
    bestSnake->prevSnake = NULL;
    bestSnake->nextSnake = NULL;

    while (snakeTmp->nextSnake){
        if (snakeTmp->currentSnake.score >= bestSnake->currentSnake.score){
            snakeListTmp = new bestSnakesList;
            snakeListTmp->currentSnake = snakeTmp->currentSnake;
            snakeListTmp->prevSnake = NULL;
            snakeListTmp->nextSnake = bestSnake;
            bestSnake->prevSnake = snakeListTmp;
            bestSnake = snakeListTmp;
        } else {
            snakeListTmp = bestSnake;
            while(snakeListTmp->nextSnake){
                if (snakeTmp->currentSnake.score >= snakeListTmp->currentSnake.score){
                    if (snakeListTmp->nextSnake){
                        snakeListSecondTmp = new bestSnakesList;
                        snakeListSecondTmp->currentSnake = snakeTmp->currentSnake;
                        snakeListSecondTmp->prevSnake = snakeListTmp->prevSnake;
                        snakeListSecondTmp->nextSnake = snakeListTmp;
                        snakeListTmp->prevSnake->nextSnake = snakeListSecondTmp;
                        snakeListTmp->prevSnake = snakeListSecondTmp;
                        break;
                    } else {
                        snakeListSecondTmp = new bestSnakesList;
                        snakeListSecondTmp->currentSnake = snakeTmp->currentSnake;
                        snakeListSecondTmp->prevSnake = snakeListTmp;
                        snakeListSecondTmp->nextSnake = NULL;
                        snakeListTmp->nextSnake = snakeListSecondTmp;
                        break;
                    }
                }
                snakeListTmp = snakeListTmp->nextSnake;
                if (!snakeListTmp->nextSnake){
                    snakeListSecondTmp = new bestSnakesList;
                    snakeListSecondTmp->currentSnake = snakeTmp->currentSnake;
                    snakeListSecondTmp->prevSnake = snakeListTmp;
                    snakeListSecondTmp->nextSnake = NULL;
                    snakeListTmp->nextSnake = snakeListSecondTmp;
                    break;
                }
            }
            
        }
        snakeTmp = snakeTmp->nextSnake;
    }

    snakeListTmp = bestSnake;
    while(snakeListTmp->nextSnake){
        #ifdef LOGS
        test << "Snake ID" << snakeListTmp->currentSnake.snakeId << ";   Score  " << snakeListTmp->currentSnake.score << std::endl;
        #endif
        snakeListTmp = snakeListTmp->nextSnake;
    }
    worstSnake = snakeListTmp->prevSnake;

    snakeListTmp = bestSnake;
    parentSnakes = new bestSnakesList;
    snakeListSecondTmp = parentSnakes;
    snakeListSecondTmp->prevSnake = NULL;
    for (int count = 0; count < ((evolutionParameters.countOfSnakes / 10) * evolutionParameters.countOfBest / 10); count++){
        snakeListSecondTmp->currentSnake = snakeListTmp->currentSnake;
        snakeListSecondTmp->nextSnake = new bestSnakesList;
        snakeListSecondTmp->nextSnake->prevSnake = snakeListSecondTmp;
        snakeListSecondTmp = snakeListSecondTmp->nextSnake;
        snakeListSecondTmp->nextSnake = NULL;

        snakeListTmp = snakeListTmp->nextSnake;
    }

    snakeListTmp = worstSnake;
    for (int count = 0; count < ((evolutionParameters.countOfSnakes / 10) * evolutionParameters.countOfWorst / 10); count++){
        snakeListSecondTmp->currentSnake = snakeListTmp->currentSnake;
        snakeListSecondTmp->nextSnake = new bestSnakesList;
        snakeListSecondTmp->nextSnake->prevSnake = snakeListSecondTmp;
        snakeListSecondTmp = snakeListSecondTmp->nextSnake;
        snakeListSecondTmp->nextSnake = NULL;

        snakeListTmp = snakeListTmp->nextSnake;
    }

    snakeListTmp = parentSnakes;
    while(snakeListTmp->nextSnake){
        #ifdef LOGS
        test << "Snake PARENTS ID" << snakeListTmp->currentSnake.snakeId << ";   Score  " << snakeListTmp->currentSnake.score << std::endl;
        #endif
        snakeListTmp = snakeListTmp->nextSnake;
    }
    #ifdef LOGS
    test.close();
    #endif
}