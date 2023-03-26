#include "evolution.h"
#include "Evolution/NeuralNetwork/standartNetwork/standartNetwork.h"
#include "Evolution/NeuralNetwork/straightNetwork/straightNetwork.h"
#include "Evolution/NeuralNetwork/simpleNetwork/simpleNetwork.h"


template <class Network>
void Evolution<Network>::run()
{
    timeout(evolutionParameters.delayDuration);

    currentScreen.clearScreen();

    evolutionParameters.turn = 0;
    evolutionParameters.score = 0;
    evolutionParameters.generation = 1;
    evolutionParameters.snakeIdCounter = 1;
    evolutionParameters.aliveSnakes = 0;

    snakes = new SnakeEvoModel<Network>[evolutionParameters.countOfSnakes];
    initSnakes(snakes);

	evolutionParameters.gameOn = true;

    while(evolutionParameters.gameOn){
        key = currentScreen.controllHandler();

        if (!toolsBar.pauseOn){
            turn(snakes);
            evolutionParameters.hightTurnsLeft--;
            evolutionParameters.turn++;
            evolutionParameters.time++;

            for (int count = 0; count < evolutionParameters.countOfSnakes; count++) {
                if (snakes[count].getIsAlive()) {
                    snakes[count].setVector(key);
                }
            }
        }

        if (evolutionParameters.aliveSnakes < 1){
            evolutionParameters.hightTurnsLeft = evolutionParameters.turnsToDeath;
            evolutionParameters.snakeIdCounter = 1;
            evolutionParameters.bestFood = 0;
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
        if (!evolutionParameters.gameOn){
            deleteSnakes(snakes);
        }
    }
    currentScreen.clearScreen();
}


template <class Network>
void Evolution<Network>::turn(SnakeEvoModel<Network> *snakes)
{
    for (int count = 0; count < evolutionParameters.countOfSnakes; count++) {
        if (snakes[count].getIsAlive()){
            snakes[count].increaseScore();
            if (snakes[count].getScore() > evolutionParameters.score){
                evolutionParameters.score = snakes[count].getScore();
                evolutionParameters.bestSnakeId = snakes[count].getId();
            }
            snakes[count].move();
        }
    }

    currentScreen.endFrame();
    currentScreen.clearScreen();
}


template <class Network>
void Evolution<Network>::drawScreen()
{
    infoBar.drawBar();
    toolsBar.drawBar();

    for (int count = 0; count < evolutionParameters.countOfSnakes; count++){
        if(snakes[count].getIsAlive()){
            snakes[count].drawField();
            squareBar.drawMap(snakes[count].getField());
            break;
        }
    }
}


template <class Network>
void Evolution<Network>::drawStuff()
{
    for (int count = 0; count < evolutionParameters.countOfSnakes; count++) {
        if(snakes[count].getIsAlive()){
            snakes[count].drawStuff();
        }
    }
}


template <class Network>
void Evolution<Network>::initSnakes(SnakeEvoModel<Network> *snakes)
{
    int snakeStartX = evolutionParameters.fullFieldSizeX / 2;
    int snakeStartY = evolutionParameters.fullFieldSizeY / 2;
    int snakeLength = evolutionParameters.snakeLength;
    int snakeColor = evolutionParameters.snakeOneBodyColor;

    for (int count = 0; count < evolutionParameters.countOfSnakes; count++) {
        snakes[count].init(new Network(), snakeStartX, snakeStartY, snakeLength, snakeColor);
    }
}


template <class Network>
void Evolution<Network>::evolveSnakes()
{
    snakesRatingList *parentSnakesList = getParentsList(snakes);


    SnakeEvoModel<Network> *nextGeneration = new SnakeEvoModel<Network>[evolutionParameters.countOfSnakes];
    int counter = 1;
    for (int count = 0; count < evolutionParameters.countOfSnakes; count++) {
        if ((evolutionParameters.fullFieldSizeY / 2) + (count * 2) + counter > (evolutionParameters.fullFieldSizeY - 3)){
            counter = 1;
        }

        nextGeneration[count].init(
            new Network(),
            evolutionParameters.fullFieldSizeX / 2,
            evolutionParameters.fullFieldSizeY / 2,
            evolutionParameters.snakeLength,
            evolutionParameters.snakeOneBodyColor
        );

        int parentsCount = ((evolutionParameters.countOfSnakes / 10) * evolutionParameters.countOfBest / 10) + ((evolutionParameters.countOfSnakes / 10) * evolutionParameters.countOfWorst / 10);
        
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> randGen(0, parentsCount - 1);

        int parentOneNum = 0;
        int parentTwoNum = 0;

        while (parentOneNum == parentTwoNum) {
            parentOneNum = randGen(generator);
            parentTwoNum = randGen(generator);
        }

        snakesRatingList *firstParent = parentSnakesList;
        for (int countX = 0; countX < parentOneNum; countX++){
            firstParent = firstParent->nextPlace;
        }

        snakesRatingList *secondParent = parentSnakesList;
        for (int countX = 0; countX < parentTwoNum; countX++){
            secondParent = secondParent->nextPlace;
        }
        
        nextGeneration[count].network->mergeNetworks(snakes[firstParent->snakeNumber].network, snakes[secondParent->snakeNumber].network);
        counter++;
    }

    deleteSnakes(snakes);
    while (parentSnakesList){
        snakesRatingList *tempPlace = parentSnakesList;
        parentSnakesList = parentSnakesList->nextPlace;
        delete tempPlace;
    }

    snakes = nextGeneration;
}


template <class Network>
void Evolution<Network>::deleteSnakes(SnakeEvoModel<Network> *snakes)
{
    for (int count = 0; count  < evolutionParameters.countOfSnakes; count++){
        snakes[count].deleteSnake();
    }
    delete[] snakes;
}


template <class Network>
typename Evolution<Network>::snakesRatingList* Evolution<Network>::getParentsList(SnakeEvoModel<Network> *snakes)
{
    snakesRatingList *firstPlace = new snakesRatingList;
    snakesRatingList *lastPlace = nullptr;
    snakesRatingList *tempRating = firstPlace;

    //Make snakes rating
    tempRating->snakeNumber = 0;
    tempRating->snakeScore = snakes[0].getScore();
    tempRating->nextPlace = nullptr;
    tempRating->prevPlace = nullptr;
    bool isSet = false;

    for (int count = 1; count < evolutionParameters.countOfSnakes; count++){
        tempRating = firstPlace;
        while(tempRating->nextPlace){
            if (snakes[count].getScore() >= tempRating->snakeScore) {
                if (!tempRating->prevPlace){
                    tempRating->prevPlace = new snakesRatingList;
                    tempRating->prevPlace->nextPlace = tempRating;
                    tempRating = tempRating->prevPlace;
                    tempRating->prevPlace = nullptr;
                    firstPlace = tempRating;
                } else {
                    snakesRatingList *newPlace = new snakesRatingList;
                    newPlace->prevPlace = tempRating->prevPlace;
                    newPlace->nextPlace = tempRating;
                    tempRating->prevPlace->nextPlace = newPlace;
                    tempRating->prevPlace = newPlace;
                    tempRating = newPlace;
                }

                tempRating->snakeNumber = count;
                tempRating->snakeScore = snakes[count].getScore();
                isSet = true;
                break;
            }
            tempRating = tempRating->nextPlace;
        }
        if (isSet){
            isSet = false;
            continue;
        }

        if (snakes[count].getScore() >= tempRating->snakeScore) {
            if (!tempRating->prevPlace){
                tempRating->prevPlace = new snakesRatingList;
                tempRating->prevPlace->nextPlace = tempRating;
                tempRating = tempRating->prevPlace;
                tempRating->prevPlace = nullptr;
                firstPlace = tempRating;
            } else {
                snakesRatingList *newPlace = new snakesRatingList;
                newPlace->prevPlace = tempRating->prevPlace;
                newPlace->nextPlace = tempRating;
                tempRating->prevPlace->nextPlace = newPlace;
                tempRating->prevPlace = newPlace;
                tempRating = newPlace;
            }
            lastPlace = tempRating->nextPlace;
            tempRating->snakeNumber = count;
            tempRating->snakeScore = snakes[count].getScore();
            continue;
        }

        tempRating->nextPlace = new snakesRatingList;
        tempRating->nextPlace->prevPlace = tempRating;
        tempRating = tempRating->nextPlace;
        tempRating->nextPlace = nullptr;
        tempRating->snakeNumber = count;
        tempRating->snakeScore = snakes[count].getScore();
        lastPlace = tempRating;
    }


    //Make parents list
    snakesRatingList *parentsList = new snakesRatingList;
    snakesRatingList *secondTempList = firstPlace;
    tempRating = parentsList;
    tempRating->prevPlace = nullptr;
    tempRating->nextPlace = nullptr;
    tempRating->snakeNumber = secondTempList->snakeNumber;
    tempRating->snakeScore = secondTempList->snakeScore;
    secondTempList = secondTempList->nextPlace;

    for (int count = 0; count < ((evolutionParameters.countOfSnakes / 10) * evolutionParameters.countOfBest / 10); count++){
        tempRating->nextPlace = new snakesRatingList;
        tempRating = tempRating->nextPlace;
        tempRating->nextPlace = nullptr;
        tempRating->snakeNumber = secondTempList->snakeNumber;
        tempRating->snakeScore = secondTempList->snakeScore;

        secondTempList = secondTempList->nextPlace;
    }

    secondTempList = lastPlace;
    for (int count = 0; count < ((evolutionParameters.countOfSnakes / 10) * evolutionParameters.countOfWorst / 10); count++){
        tempRating->nextPlace = new snakesRatingList;
        tempRating = tempRating->nextPlace;
        tempRating->nextPlace = nullptr;
        tempRating->snakeNumber = secondTempList->snakeNumber;
        tempRating->snakeScore = secondTempList->snakeScore;

        secondTempList = secondTempList->prevPlace;
    }

    while(firstPlace) {
        tempRating = firstPlace;
        firstPlace = firstPlace->nextPlace;
        delete tempRating;
    }


    return parentsList;
}


template class Evolution<StandartNetwork>;

template class Evolution<StraightNetwork>;

template class Evolution<SimpleNetwork>;