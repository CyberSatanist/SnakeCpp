#include "straightNetwork.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>
#include <math.h>

extern EvolutionParameters evolutionParameters;

StraightNetwork::StraightNetwork()
{
    initNetwork();
    initLayers();
    initNeuronConnections();
}


void StraightNetwork::initNetwork()
{
    evolutionParameters.layerIdCounter = 1;
    layersList = nullptr;
    int countOfLayers = 2;
    addLayers(countOfLayers);

}


void StraightNetwork::addLayers(int countOfLayers)
{
    for (int count = 0; count < countOfLayers; count++){
        if(!layersList){
            layersList = new LayersList;
            layersListTmp = layersList;

            firstLayer = new NeuronsList;
            layersListTmp->currentNeuronsList = firstLayer;
            layersListTmp->layerId = evolutionParameters.layerIdCounter;
            evolutionParameters.layerIdCounter++;
            layersListTmp->nextLayer = nullptr;
        } else {
            layersListTmp = layersList;
            while(layersList->nextLayer){
                layersList = layersList->nextLayer;
            }

            layersListTmp->nextLayer = new LayersList;
            layersListTmp = layersListTmp->nextLayer;
            layersListTmp->layerId = evolutionParameters.layerIdCounter;
            evolutionParameters.layerIdCounter++;

            layersListTmp->currentNeuronsList = new NeuronsList;
            lastLayer = layersListTmp->currentNeuronsList;
            layersListTmp->nextLayer = nullptr;
        }
    }
}


void StraightNetwork::initLayers()
{
    layersListTmp = layersList;

    //first layer
    addNeurons(layersListTmp->currentNeuronsList, evolutionParameters.firstLayerNeuronCount);
    layersListTmp = layersListTmp->nextLayer;

    //last layer
    addNeurons(layersListTmp->currentNeuronsList, evolutionParameters.lastLayerNeuronCount);
}


void StraightNetwork::addNeurons(NeuronsList *firstNeuron, int neuronsCount)
{
    NeuronsList *tempLayer = nullptr;

    tempLayer = firstNeuron;
    tempLayer->currentNeuron = new StraightNeuron;
    lastNeuron = tempLayer->currentNeuron;
    tempLayer->nextNeuron = nullptr;

    for (int count = 1; count < neuronsCount; count++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
        tempLayer->currentNeuron = new StraightNeuron;
        lastNeuron = tempLayer->currentNeuron;
        tempLayer->nextNeuron = nullptr;
    }
}


void StraightNetwork::initNeuronConnections()
{
    NeuronsList *tempLayer = nullptr;

    layersListTmp = layersList;
    while(layersListTmp){
        tempLayer = layersListTmp->currentNeuronsList;

        while (tempLayer->nextNeuron){
            tempLayer->currentNeuron->tmpConnection = new StraightNeuron::Connections;
            tempLayer->currentNeuron->tmpConnection->nextConnection = nullptr;
            tempLayer->currentNeuron->firstConnection = tempLayer->currentNeuron->tmpConnection;
            if (layersListTmp->nextLayer){
                nextLayer = layersListTmp->nextLayer->currentNeuronsList;
                while(nextLayer->nextNeuron){
                    tempLayer->currentNeuron->tmpConnection->currentNeuron = nextLayer->currentNeuron;
                    tempLayer->currentNeuron->tmpConnection->nextConnection = new StraightNeuron::Connections;
                    tempLayer->currentNeuron->tmpConnection = tempLayer->currentNeuron->tmpConnection->nextConnection;
                    tempLayer->currentNeuron->tmpConnection->nextConnection = nullptr;
                    nextLayer = nextLayer->nextNeuron;
                }
            }
            tempLayer = tempLayer->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
    }
}


int StraightNetwork::useMind(EvoField evoField, int headX, int headY)
{

    NeuronsList *tempLayer = nullptr;
    int radius = (sqrt(evolutionParameters.firstLayerNeuronCount) -1) / 2;

    tempLayer = layersList->currentNeuronsList;
    for (int countX = (headX - radius); countX <= (headX + radius); countX++){
        for (int countY = (headY - radius); countY <= (headY + radius); countY++){
            if (
                (countX > evoField.currentBeginX)
                & (countX < evoField.fullSizeX)
                & (countY > evoField.currentBeginY)
                & (countY < evoField.fullSizeY)
            ) {
                switch (evoField.getCell(countX, countY)){
                    case Field::Food:
                        tempLayer->currentNeuron->input = 1; //1->0
                        break;
                    case Field::Free:
                        tempLayer->currentNeuron->input = 0;//0->33
                        break;
                    case Field::Snake:
                        tempLayer->currentNeuron->input = -1; //-0->33
                    break;
                    case Field::Wall:
                        tempLayer->currentNeuron->input = -2; //-1->0
                    break;
                }
            } else {
                tempLayer->currentNeuron->input = -2; 
            }
            tempLayer = tempLayer->nextNeuron;
        }
    }
    neuronActivity();

    layersListTmp = layersList;
    while(layersListTmp->nextLayer){
        layersListTmp = layersListTmp->nextLayer;
    }
    return lastNeuron->direction;
}


void StraightNetwork::neuronActivity()
{

    NeuronsList *tempLayer = nullptr;
    layersListTmp = layersList;
    tempLayer = layersListTmp->currentNeuronsList;
    while (tempLayer->nextNeuron){
        tempLayer->currentNeuron->tmpConnection = tempLayer->currentNeuron->firstConnection;
        while (tempLayer->currentNeuron->tmpConnection->nextConnection){
            switch (tempLayer->currentNeuron->input) {
                case -2:
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->addResultReaction(tempLayer->currentNeuron->wallReaction);
                    break;
                case -1:
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->addResultReaction(tempLayer->currentNeuron->snakeReaction);
                    break;
                case 1:
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->addResultReaction(tempLayer->currentNeuron->foodReaction);
                    break;
                case 0:
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->addResultReaction(tempLayer->currentNeuron->freeReaction);
                    break;
            }
            tempLayer->currentNeuron->tmpConnection = tempLayer->currentNeuron->tmpConnection->nextConnection;
        }
        tempLayer = tempLayer->nextNeuron;
    }

    layersListTmp = layersListTmp->nextLayer;
    tempLayer = layersListTmp->currentNeuronsList;

    for (int neuronCount = 0; neuronCount < (evolutionParameters.lastLayerNeuronCount - 1); neuronCount++){
        lastNeuron->resultReaction->up += tempLayer->currentNeuron->resultReaction->up;
        lastNeuron->addResultReaction(tempLayer->currentNeuron->resultReaction);
        tempLayer = tempLayer->nextNeuron;
    }

    if ((lastNeuron->resultReaction->up > lastNeuron->resultReaction->down) & (lastNeuron->resultReaction->up > lastNeuron->resultReaction->left) & (lastNeuron->resultReaction->up > lastNeuron->resultReaction->right)) {
        lastNeuron->direction = Screen::controll_keys::UP;
    } else if ((lastNeuron->resultReaction->down > lastNeuron->resultReaction->up) & (lastNeuron->resultReaction->down > lastNeuron->resultReaction->left) & (lastNeuron->resultReaction->down > lastNeuron->resultReaction->right)) {
        lastNeuron->direction = Screen::controll_keys::DOWN;
    } else if ((lastNeuron->resultReaction->left > lastNeuron->resultReaction->up) & (lastNeuron->resultReaction->left > lastNeuron->resultReaction->down) & (lastNeuron->resultReaction->left > lastNeuron->resultReaction->right)) {
        lastNeuron->direction = Screen::controll_keys::LEFT;
    } else if ((lastNeuron->resultReaction->right > lastNeuron->resultReaction->up) & (lastNeuron->resultReaction->right > lastNeuron->resultReaction->down) & (lastNeuron->resultReaction->right > lastNeuron->resultReaction->left)) {
        lastNeuron->direction = Screen::controll_keys::RIGHT;
    }
}




void StraightNetwork::mergeNetworks(LayersList *parentOne, LayersList *parentTwo)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(0, 100);
    int randChance;

    layersListTmp = layersList;

    LayersList *layersListParentOne;
    layersListParentOne = parentOne;

    LayersList *layersListParentTwo;
    layersListParentTwo = parentTwo;

    NeuronsList *layerParentOne = nullptr;
    NeuronsList *layerParentTwo = nullptr;

    NeuronsList *tempLayer = nullptr;

    while(layersListTmp){
        tempLayer = layersListTmp->currentNeuronsList;
        layerParentOne = layersListParentOne->currentNeuronsList;
        layerParentTwo = layersListParentTwo->currentNeuronsList;
        while (tempLayer->nextNeuron){
            randChance = randGen(generator);
            if ((randChance < (evolutionParameters.mutationChance / 2)) | (randChance >  (100 -evolutionParameters.mutationChance))){
                tempLayer->currentNeuron->randomSynapse(tempLayer->currentNeuron->foodReaction);
                tempLayer->currentNeuron->randomSynapse(tempLayer->currentNeuron->wallReaction);
                tempLayer->currentNeuron->randomSynapse(tempLayer->currentNeuron->snakeReaction);
                tempLayer->currentNeuron->randomSynapse(tempLayer->currentNeuron->freeReaction);
            } else if (randChance < 50) {
                tempLayer->currentNeuron->mergeReactions(layerParentOne->currentNeuron);
            } else {
                tempLayer->currentNeuron->mergeReactions(layerParentTwo->currentNeuron);
            }
            tempLayer = tempLayer->nextNeuron;
            layerParentOne = layerParentOne->nextNeuron;
            layerParentTwo = layerParentTwo->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
        layersListParentOne = layersListParentOne->nextLayer;
        layersListParentTwo = layersListParentTwo->nextLayer;
    }
}


void StraightNetwork::deleteNetwork()
{
    NeuronsList *tempSecondLayer = nullptr;
    NeuronsList *tempLayer = nullptr;

    layersListTmp = layersList;
    while(layersListTmp){
        tempLayer = layersListTmp->currentNeuronsList;
        while (tempLayer){
            tempSecondLayer = tempLayer;
            tempLayer = tempLayer->nextNeuron;
            tempSecondLayer->currentNeuron->deleteNeuron();
            tempSecondLayer->nextNeuron = nullptr;
            delete tempSecondLayer->currentNeuron;
            tempSecondLayer->currentNeuron = nullptr;
            delete tempSecondLayer;
            tempSecondLayer = nullptr;
        }
        //tempLayer->currentNeuron->deleteNeuron();
        //delete tempLayer->currentNeuron;
        delete tempLayer;
        tempLayer = nullptr;

        layersListSecondTmp = layersListTmp;
        layersListTmp = layersListTmp->nextLayer;
        layersListSecondTmp->nextLayer = nullptr;
        delete layersListSecondTmp;
        layersListSecondTmp = nullptr;
    }
    delete layersListTmp;
    layersListTmp = nullptr;
    firstLayer = nullptr;
    lastLayer = nullptr;
    nextLayer = nullptr;
    lastNeuron = nullptr;
    layersList = nullptr;
}