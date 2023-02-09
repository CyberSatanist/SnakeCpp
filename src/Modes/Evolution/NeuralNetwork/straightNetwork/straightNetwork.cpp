#include "straightNetwork.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>
#include <math.h>

extern EvolutionParameters evolutionParameters;

StraightNetwork::StraightNetwork()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(-100, 100);

    foodNeuronsUp = new int [evolutionParameters.firstLayerNeuronCount];
    foodNeuronsDown = new int [evolutionParameters.firstLayerNeuronCount];
    foodNeuronsLeft = new int [evolutionParameters.firstLayerNeuronCount];
    foodNeuronsRight = new int [evolutionParameters.firstLayerNeuronCount];

    wallNeuronsUp = new int [evolutionParameters.firstLayerNeuronCount];
    wallNeuronsDown = new int [evolutionParameters.firstLayerNeuronCount];
    wallNeuronsLeft = new int [evolutionParameters.firstLayerNeuronCount];
    wallNeuronsRight = new int [evolutionParameters.firstLayerNeuronCount];
    for (int neuronCount = 0; neuronCount < evolutionParameters.firstLayerNeuronCount; neuronCount++){
        foodNeuronsUp[neuronCount] = randGen(generator);
        foodNeuronsDown[neuronCount] = randGen(generator);
        foodNeuronsLeft[neuronCount] = randGen(generator);
        foodNeuronsRight[neuronCount] = randGen(generator);

        wallNeuronsUp[neuronCount] = randGen(generator);
        wallNeuronsDown[neuronCount] = randGen(generator);
        wallNeuronsLeft[neuronCount] = randGen(generator);
        wallNeuronsRight[neuronCount] = randGen(generator);
    }
}


StraightNetwork::~StraightNetwork()
{
    delete[] foodNeuronsUp;
    delete[] foodNeuronsDown;
    delete[] foodNeuronsLeft;
    delete[] foodNeuronsRight;

    delete[] wallNeuronsUp;
    delete[] wallNeuronsDown;
    delete[] wallNeuronsLeft;
    delete[] wallNeuronsRight;
}


int StraightNetwork::useMind(EvoField &evoField, int headX, int headY)
{
    int radius = (sqrt(evolutionParameters.firstLayerNeuronCount) -1) / 2;
    int neuronCount = 0;
    int result = 0;

    for (int countX = (headX - radius); countX <= (headX + radius); countX++){
        for (int countY = (headY - radius); countY <= (headY + radius); countY++, neuronCount++){
            if (
                (countX > evoField.getCurrentBeginX())
                && (countX < evoField.getFullSizeX())
                && (countY > evoField.getCurrentBeginY())
                && (countY < evoField.getFullSizeY())
            ) {
                switch (evoField.getCell(countX, countY)){
                    //case Field::Free:
                    //    result = validateResult(result, wallNeurons[neuronCount]);
                    //    break;
                    case Field::Food:
                        up = validateResult(up, foodNeuronsUp[neuronCount]);
                        down = validateResult(down, foodNeuronsDown[neuronCount]);
                        left = validateResult(left, foodNeuronsLeft[neuronCount]);
                        right = validateResult(right, foodNeuronsRight[neuronCount]);
                        break;
                    case Field::Snake:
                        up = validateResult(up, wallNeuronsUp[neuronCount]);
                        down = validateResult(down, wallNeuronsDown[neuronCount]);
                        left = validateResult(left, wallNeuronsLeft[neuronCount]);
                        right = validateResult(right, wallNeuronsRight[neuronCount]);
                        break;
                    case Field::Wall:
                        up = validateResult(up, wallNeuronsUp[neuronCount]);
                        down = validateResult(down, wallNeuronsDown[neuronCount]);
                        left = validateResult(left, wallNeuronsLeft[neuronCount]);
                        right = validateResult(right, wallNeuronsRight[neuronCount]);
                        break;
                }
            } else {
                up = validateResult(up, wallNeuronsUp[neuronCount]);
                down = validateResult(down, wallNeuronsDown[neuronCount]);
                left = validateResult(left, wallNeuronsLeft[neuronCount]);
                right = validateResult(right, wallNeuronsRight[neuronCount]);
            }
        }
    }

    return neuronActivity(result);
}


int StraightNetwork::validateResult(int result, int weight)
{
    result += weight;
    if (result > 100){
        return 100 - (result - 100);
    } else if (result < -100) {
        return -100 - (result + 100);
    }
    return result;
}


int StraightNetwork::neuronActivity(int result)
{
    if ((up > down) && (up > left) && (up > right)) {
        return Screen::controll_keys::UP;
    } else if ((down > up) && (down > left) && (down > right)) {
        return Screen::controll_keys::DOWN;
    } else if ((left > up) && (left > down) && (left >right)) {
        return Screen::controll_keys::LEFT;
    } else {
        return Screen::controll_keys::RIGHT;
    }
}


void StraightNetwork::mergeNetworks(StraightNetwork *parentOne, StraightNetwork *parentTwo)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(-100, 100);

    std::mt19937 parentGenerator(random_device());
    std::uniform_int_distribution<> parentRandom(0, 100);

    for (int neuronCount = 0; neuronCount < evolutionParameters.firstLayerNeuronCount; neuronCount++){
        int randChance = parentRandom(parentGenerator);
        if ((randChance < (evolutionParameters.mutationChance / 2)) || (randChance >  (100 -evolutionParameters.mutationChance))){
            wallNeuronsUp[neuronCount] = randGen(generator) / 10;
            wallNeuronsDown[neuronCount] = randGen(generator) / 10;
            wallNeuronsLeft[neuronCount] = randGen(generator) / 10;
            wallNeuronsRight[neuronCount] = randGen(generator) / 10;

            foodNeuronsUp[neuronCount] = randGen(generator) / 10;
            foodNeuronsDown[neuronCount] = randGen(generator) / 10;
            foodNeuronsLeft[neuronCount] = randGen(generator) / 10;
            foodNeuronsRight[neuronCount] = randGen(generator) / 10;
        } else if (randChance < 50) {
            wallNeuronsUp[neuronCount] = parentOne->wallNeuronsUp[neuronCount];
            wallNeuronsDown[neuronCount] = parentOne->wallNeuronsDown[neuronCount];
            wallNeuronsLeft[neuronCount] = parentOne->wallNeuronsLeft[neuronCount];
            wallNeuronsRight[neuronCount] = parentOne->wallNeuronsRight[neuronCount];

            foodNeuronsUp[neuronCount] = parentOne->foodNeuronsUp[neuronCount];
            foodNeuronsDown[neuronCount] = parentOne->foodNeuronsDown[neuronCount];
            foodNeuronsLeft[neuronCount] = parentOne->foodNeuronsLeft[neuronCount];
            foodNeuronsRight[neuronCount] = parentOne->foodNeuronsRight[neuronCount];
        } else {
            wallNeuronsUp[neuronCount] = parentTwo->wallNeuronsUp[neuronCount];
            wallNeuronsDown[neuronCount] = parentTwo->wallNeuronsDown[neuronCount];
            wallNeuronsLeft[neuronCount] = parentTwo->wallNeuronsLeft[neuronCount];
            wallNeuronsRight[neuronCount] = parentTwo->wallNeuronsRight[neuronCount];

            foodNeuronsUp[neuronCount] = parentTwo->foodNeuronsUp[neuronCount];
            foodNeuronsDown[neuronCount] = parentTwo->foodNeuronsDown[neuronCount];
            foodNeuronsLeft[neuronCount] = parentTwo->foodNeuronsLeft[neuronCount];
            foodNeuronsRight[neuronCount] = parentTwo->foodNeuronsRight[neuronCount];
        }
    }
}