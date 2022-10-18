#include "straightNeuron.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>

extern EvolutionParameters evolutionParameters;

StraightNeuron::StraightNeuron()
{
    neuronId = evolutionParameters.neuronIdCounter;
    evolutionParameters.neuronIdCounter++;

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(-10, 10);

    foodReaction = new Reactions;
    foodReaction->up = randGen(generator);
    foodReaction->down = randGen(generator);
    foodReaction->left = randGen(generator);
    foodReaction->right = randGen(generator);

    wallReaction = new Reactions;
    wallReaction->up = randGen(generator);
    wallReaction->down = randGen(generator);
    wallReaction->left = randGen(generator);
    wallReaction->right = randGen(generator);

    freeReaction = new Reactions;
    freeReaction->up = randGen(generator);
    freeReaction->down = randGen(generator);
    freeReaction->left = randGen(generator);
    freeReaction->right = randGen(generator);

    snakeReaction = new Reactions;
    snakeReaction->up = randGen(generator);
    snakeReaction->down = randGen(generator);
    snakeReaction->left = randGen(generator);
    snakeReaction->right = randGen(generator);

    resultReaction = new Reactions;
}


void StraightNeuron::deleteNeuron()
{
    delete resultReaction;
    delete snakeReaction;
    delete freeReaction;
    delete wallReaction;
    delete foodReaction;

    if(firstConnection){
        tmpConnection = firstConnection;
        while (tmpConnection->nextConnection){
            tmpSecondConnection = tmpConnection;
            tmpConnection = tmpConnection->nextConnection;
            delete tmpSecondConnection;
        }
        delete tmpConnection;
    }
}