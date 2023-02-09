#include "simpleNetwork.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>
#include <math.h>

extern EvolutionParameters evolutionParameters;


SimpleNetwork::SimpleNetwork()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(1, 19);

    foodNeurons = new float [evolutionParameters.firstLayerNeuronCount];
    wallNeurons = new float [evolutionParameters.firstLayerNeuronCount];
    for (int neuronCount = 0; neuronCount < evolutionParameters.firstLayerNeuronCount; neuronCount++){
        foodNeurons[neuronCount] = randGen(generator) / 10;
        wallNeurons[neuronCount] = randGen(generator) / 10;
    }
}


SimpleNetwork::~SimpleNetwork()
{
    delete[] foodNeurons;
    delete[] wallNeurons;
}


int SimpleNetwork::useMind(EvoField &evoField, int headX, int headY)
{
    int radius = (sqrt(evolutionParameters.firstLayerNeuronCount) -1) / 2;
    int neuronCount = 0;
    float result = 1;

    for (int countX = (headX - radius); countX <= (headX + radius); countX++){
        for (int countY = (headY - radius); countY <= (headY + radius); countY++, neuronCount++){
            if (
                (countX > evoField.getCurrentBeginX())
                && (countX < evoField.getFullSizeX())
                && (countY > evoField.getCurrentBeginY())
                && (countY < evoField.getFullSizeY())
            ) {
                switch (evoField.getCell(countX, countY)){
                    case Field::Free:
                        result = validateResult(result, wallNeurons[neuronCount] * 1.75);
                        break;
                    case Field::Food:
                        result = validateResult(result, wallNeurons[neuronCount] * 1.25);
                        break;
                    case Field::Snake:
                        result = validateResult(result, wallNeurons[neuronCount] * 0.75);
                        break;
                    case Field::Wall:
                        result = validateResult(result, wallNeurons[neuronCount] * 0.25);
                        break;
                }
            } else {
                result = validateResult(result, wallNeurons[neuronCount] * 0.25); 
            }
        }
    }

    return neuronActivity(result);
}


float SimpleNetwork::validateResult(float result, float weight)
{
    result *= weight;
    if (result > 1.9){
        result -= 1.9;
    } else if (result < 0.1) {
        result = 1.9 - result;
    }
    return result;
}


int SimpleNetwork::neuronActivity(float result)
{
    if (result < 0.5) {
        return Screen::controll_keys::UP;
    } else if (result < 1) {
        return Screen::controll_keys::DOWN;
    } else if (result < 1.5) {
        return Screen::controll_keys::LEFT;
    } else {
        return Screen::controll_keys::RIGHT;
    }
}


void SimpleNetwork::mergeNetworks(SimpleNetwork *parentOne, SimpleNetwork *parentTwo)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(1, 19);

    std::mt19937 parentGenerator(random_device());
    std::uniform_int_distribution<> parentRandom(0, 100);

    for (int neuronCount = 0; neuronCount < evolutionParameters.firstLayerNeuronCount; neuronCount++){
        int randChance = parentRandom(parentGenerator);
        if ((randChance < (evolutionParameters.mutationChance / 2)) || (randChance >  (100 -evolutionParameters.mutationChance))){
            wallNeurons[neuronCount] = randGen(generator) / 10;
            foodNeurons[neuronCount] = randGen(generator) / 10;
        } else if (randChance < 50) {
            wallNeurons[neuronCount] = parentOne->wallNeurons[neuronCount];
            foodNeurons[neuronCount] = parentOne->foodNeurons[neuronCount];
        } else {
            wallNeurons[neuronCount] = parentTwo->wallNeurons[neuronCount];
            foodNeurons[neuronCount] = parentTwo->foodNeurons[neuronCount];
        }
    }
}