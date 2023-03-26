#include "standartNetwork.h"
#include "Evolution/Parameters/evolutionParameters.h"
#include <random>
#include <math.h>

extern EvolutionParameters evolutionParameters;

StandartNetwork::StandartNetwork()
{
    initNetwork();
}


StandartNetwork::~StandartNetwork()
{
    delete[] inputLayer;
    for (int count = 0; count < evolutionParameters.countOfHiddenLayers; count++) {
        delete[] hiddenLayers[count];
    }
    delete[] hiddenLayers;
    delete[] outputLayer;
}


void StandartNetwork::initNetwork()
{
    inputLayer = new float [evolutionParameters.inputLayerNeuronCount];
    initLayer(inputLayer, evolutionParameters.inputLayerNeuronCount);

    hiddenLayers = new float* [evolutionParameters.countOfHiddenLayers];
    for (int count = 0; count < evolutionParameters.countOfHiddenLayers; count++){
        hiddenLayers[count] = new float [evolutionParameters.hiddenLayerNeuronCount];
        initLayer(hiddenLayers[count], evolutionParameters.hiddenLayerNeuronCount);
    }

    outputLayer = new float [evolutionParameters.outputLayerNeuronCount];
    initLayer(outputLayer, evolutionParameters.outputLayerNeuronCount);
}

void StandartNetwork::initLayer(float *layer, int neuronsCount)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(1, 19);

    for (int count = 0; count < neuronsCount; count++){
        layer[count] = randGen(generator) / 10;
    }
}


int StandartNetwork::useMind(EvoField &evoField, int headX, int headY)
{
    int radius = (sqrt(evolutionParameters.inputLayerNeuronCount) -1) / 2;

    int neuronCount = 0;

    for (int countX = (headX - radius); countX <= (headX + radius); countX++){
        for (int countY = (headY - radius); countY <= (headY + radius); countY++, neuronCount++){
            if (
                (countX > evoField.getCurrentBeginX())
                && (countX < evoField.getFullSizeX())
                && (countY > evoField.getCurrentBeginY())
                && (countY < evoField.getFullSizeY())
            ) {
                switch (evoField.getCell(countX, countY)){
                    case Field::Food:
                        inputLayer[neuronCount] = 2;
                        break;
                    case Field::Free:
                        inputLayer[neuronCount] = 1;
                        break;
                    case Field::Snake:
                        inputLayer[neuronCount] = 0;
                        break;
                    case Field::Wall:
                        inputLayer[neuronCount] = 0;
                        break;
                }
            } else {
                inputLayer[neuronCount] = 0;
            }
        }
    }

    return neuronActivity();
}


int StandartNetwork::neuronActivity()
{
    float *resultVector;
    float *tempVector;

    if (evolutionParameters.countOfHiddenLayers > 0) {
        resultVector = sumVectors(inputLayer, evolutionParameters.inputLayerNeuronCount, hiddenLayers[0], evolutionParameters.hiddenLayerNeuronCount);
        for (int count = 1; count < evolutionParameters.countOfHiddenLayers; count++) {
            tempVector = sumVectors(resultVector, evolutionParameters.hiddenLayerNeuronCount, hiddenLayers[count], evolutionParameters.hiddenLayerNeuronCount);
            delete[] resultVector;
            resultVector = tempVector;
        }
        tempVector = sumVectors(resultVector, evolutionParameters.hiddenLayerNeuronCount, outputLayer, evolutionParameters.outputLayerNeuronCount);
        delete[] resultVector;
        resultVector = tempVector;
    } else {
        resultVector = sumVectors(inputLayer, evolutionParameters.inputLayerNeuronCount, outputLayer, evolutionParameters.outputLayerNeuronCount);
    }

    int result;
    if ((resultVector[0] >= resultVector[1]) && (resultVector[0] >= resultVector[2]) && (resultVector[0] >= resultVector[3])) {
        result = Screen::controll_keys::UP;
    } else if ((resultVector[1] >= resultVector[0]) && (resultVector[1] >= resultVector[2]) && (resultVector[1] >= resultVector[3])) {
        result = Screen::controll_keys::DOWN;
    } else if ((resultVector[2] >= resultVector[0]) && (resultVector[2] >= resultVector[1]) && (resultVector[2] >= resultVector[3])) {
        result = Screen::controll_keys::LEFT;
    } else {
        result = Screen::controll_keys::RIGHT;
    }

    delete[] resultVector;
    return result;
}


float * StandartNetwork::sumVectors(float *firstVector, int firstVectorSize, float *secondVector, int secondVectorSize)
{
    float *resultVector = new float [secondVectorSize];

    for (int countX = 0; countX < secondVectorSize; countX++) {
        resultVector[countX] = 0;
        for (int countY = 0; countY < firstVectorSize; countY++){
            resultVector[countX] += secondVector[countX] * firstVector[countY];
        }
    }

    return resultVector;
}



void StandartNetwork::mergeNetworks(StandartNetwork *parentOne, StandartNetwork *parentTwo)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> parentRandom(0, 100);
    std::uniform_int_distribution<> randSynapse(1, 19);

    for (int neuronCount = 0; neuronCount < evolutionParameters.inputLayerNeuronCount; neuronCount++){
        int randChance = parentRandom(generator);
        if ((randChance < (evolutionParameters.mutationChance / 2)) || (randChance >  (100 -evolutionParameters.mutationChance))){
            inputLayer[neuronCount] = randSynapse(generator) / 10;
        } else if (randChance < 50) {
            inputLayer[neuronCount] = parentOne->inputLayer[neuronCount];
        } else {
            inputLayer[neuronCount] = parentTwo->inputLayer[neuronCount];
        }
    }

    for (int layerCount = 0; layerCount < evolutionParameters.countOfHiddenLayers; layerCount++){
        for (int neuronCount = 0; neuronCount < evolutionParameters.hiddenLayerNeuronCount; neuronCount++){
            int randChance = parentRandom(generator);
            if ((randChance < (evolutionParameters.mutationChance / 2)) || (randChance >  (100 -evolutionParameters.mutationChance))){
                hiddenLayers[layerCount][neuronCount] = randSynapse(generator) / 10;
            } else if (randChance < 50) {
                hiddenLayers[layerCount][neuronCount] = parentOne->hiddenLayers[layerCount][neuronCount];
            } else {
                hiddenLayers[layerCount][neuronCount] = parentTwo->hiddenLayers[layerCount][neuronCount];
            }
        }
    }

    for (int neuronCount = 0; neuronCount < evolutionParameters.outputLayerNeuronCount; neuronCount++){
        int randChance = parentRandom(generator);
        if ((randChance < (evolutionParameters.mutationChance / 2)) || (randChance >  (100 -evolutionParameters.mutationChance))){
            outputLayer[neuronCount] = randSynapse(generator) / 10;
        } else if (randChance < 50) {
            outputLayer[neuronCount] = parentOne->outputLayer[neuronCount];
        } else {
            outputLayer[neuronCount] = parentTwo->outputLayer[neuronCount];
        }
    }
}