#include "straightNeuron.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>

extern EvolutionParameters evolutionParameters;

StraightNeuron::StraightNeuron()
{
    neuronId = evolutionParameters.neuronIdCounter;
    evolutionParameters.neuronIdCounter++;


    foodReaction = new Reactions;
    randomSynapse(foodReaction);

    wallReaction = new Reactions;
    randomSynapse(wallReaction);

    freeReaction = new Reactions;
    randomSynapse(freeReaction);

    snakeReaction = new Reactions;
    randomSynapse(snakeReaction);

    resultReaction = new Reactions;

    firstConnection = NULL;
}


void StraightNeuron::addResultReaction(Reactions *reaction)
{
    resultReaction->up += reaction->up;
    validateReaction(&(resultReaction->up));

    resultReaction->down += reaction->down;
    validateReaction(&(resultReaction->down));

    resultReaction->left += reaction->left;
    validateReaction(&(resultReaction->left));

    resultReaction->right += reaction->right;
    validateReaction(&(resultReaction->right));
}


void StraightNeuron::validateReaction(int *reactionInt)
{
    if (*reactionInt > 100){
        *reactionInt = 100 - (*reactionInt - 100);
    } else if (*reactionInt < -100){
        *reactionInt = -100 - (*reactionInt + 100);
    }
}


void StraightNeuron::randomSynapse(Reactions *reaction)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(-10, 10);

    reaction->up = randGen(generator);
    reaction->down = randGen(generator);
    reaction->left = randGen(generator);
    reaction->right = randGen(generator);
}


void StraightNeuron::mergeReactions(StraightNeuron *parentNeuron)
{
    setCurrentReaction(foodReaction, parentNeuron->foodReaction);
    setCurrentReaction(snakeReaction, parentNeuron->snakeReaction);
    setCurrentReaction(wallReaction, parentNeuron->wallReaction);
}


void StraightNeuron::setCurrentReaction(Reactions *childReaction, Reactions *parentReaction)
{
    childReaction->up = parentReaction->up;
    childReaction->down = parentReaction->down;
    childReaction->left = parentReaction->left;
    childReaction->right = parentReaction->right;
}


void StraightNeuron::deleteNeuron()
{
    delete resultReaction;
    resultReaction = nullptr;
    delete snakeReaction;
    snakeReaction = nullptr;
    delete freeReaction;
    freeReaction = nullptr;
    delete wallReaction;
    wallReaction = nullptr;
    delete foodReaction;
    foodReaction = nullptr;

    if(firstConnection){
        tmpConnection = firstConnection;
        while (tmpConnection){
            tmpSecondConnection = tmpConnection;
            tmpConnection = tmpConnection->nextConnection;
            delete tmpSecondConnection;
            tmpSecondConnection = nullptr;
        }
        tmpConnection = nullptr;
    }
}