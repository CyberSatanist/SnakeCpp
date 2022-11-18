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
                        tempLayer->currentNeuron->input = -1; //-1->0
                    break;
                }
            } else {
                tempLayer->currentNeuron->input = -1; 
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
    layersListTmp = layersList;
    tempLayer = layersListTmp->currentNeuronsList;
    while (tempLayer->nextNeuron){
        tempLayer->currentNeuron->tmpConnection = tempLayer->currentNeuron->firstConnection;
        while (tempLayer->currentNeuron->tmpConnection->nextConnection){
            switch (tempLayer->currentNeuron->input) {
                case -1:
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up += tempLayer->currentNeuron->wallReaction->up;
                    if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up > 100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up = 100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up - 100);
                    } else if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up < -100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up = -100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up + 100);
                    }
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down += tempLayer->currentNeuron->wallReaction->down;
                    if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down > 100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down = 100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down - 100);
                    } else if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down < -100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down = -100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down + 100);
                    }
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left += tempLayer->currentNeuron->wallReaction->left;
                    if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left > 100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left = 100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left - 100);
                    } else if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left < -100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left = -100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left + 100);
                    }
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right += tempLayer->currentNeuron->wallReaction->right;
                    if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right > 100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right = 100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right - 100);
                    } else if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right < -100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right = -100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right + 100);
                    }
                    break;
                case 1:
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up += tempLayer->currentNeuron->foodReaction->up;
                    if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up > 100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up = 100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up - 100);
                    } else if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up < -100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up = -100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->up + 100);
                    }
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down += tempLayer->currentNeuron->foodReaction->down;
                    if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down > 100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down = 100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down - 100);
                    } else if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down < -100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down = -100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->down + 100);
                    }
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left += tempLayer->currentNeuron->foodReaction->left;
                    if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left > 100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left = 100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left - 100);
                    } else if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left < -100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left = -100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->left + 100);
                    }
                    tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right += tempLayer->currentNeuron->foodReaction->right;
                    if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right > 100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right = 100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right - 100);
                    } else if (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right < -100){
                        tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right = -100 - (tempLayer->currentNeuron->tmpConnection->currentNeuron->resultReaction->right + 100);
                    }
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
        if (lastNeuron->resultReaction->up > 100) {
            lastNeuron->resultReaction->up = 100 - (lastNeuron->resultReaction->up - 100);
        } else if (lastNeuron->resultReaction->up < -100) {
            lastNeuron->resultReaction->up = -100 - (lastNeuron->resultReaction->up + 100);
        }
        lastNeuron->resultReaction->down += tempLayer->currentNeuron->resultReaction->down;
        if (lastNeuron->resultReaction->down > 100) {
            lastNeuron->resultReaction->down = 100 - (lastNeuron->resultReaction->down - 100);
        } else if (lastNeuron->resultReaction->down < -100) {
            lastNeuron->resultReaction->down = -100 - (lastNeuron->resultReaction->down + 100);
        }
        lastNeuron->resultReaction->left += tempLayer->currentNeuron->resultReaction->left;
        if (lastNeuron->resultReaction->left > 100) {
            lastNeuron->resultReaction->left = 100 - (lastNeuron->resultReaction->left - 100);
        } else if (lastNeuron->resultReaction->left < -100) {
            lastNeuron->resultReaction->left = -100 - (lastNeuron->resultReaction->left + 100);
        }
        lastNeuron->resultReaction->right += tempLayer->currentNeuron->resultReaction->right;
        if (lastNeuron->resultReaction->right > 100) {
            lastNeuron->resultReaction->right = 100 - (lastNeuron->resultReaction->right - 100);
        } else if (lastNeuron->resultReaction->right < -100) {
            lastNeuron->resultReaction->right = -100 - (lastNeuron->resultReaction->right + 100);
        }
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
    std::uniform_int_distribution<> randSynapse(-10, 10);
    int randChance;

    layersListTmp = layersList;
    layersListParentOne = parentOne;
    layersListParentTwo = parentTwo;

    int layer = 1;
    int neuron = 1;
    while(layersListTmp){
        tempLayer = layersListTmp->currentNeuronsList;
        layerParentOne = layersListParentOne->currentNeuronsList;
        layerParentTwo = layersListParentTwo->currentNeuronsList;
        while (tempLayer->nextNeuron){
            randChance = randGen(generator);
            if ((randChance < (evolutionParameters.mutationChance / 2)) | (randChance >  (100 -evolutionParameters.mutationChance))){
                tempLayer->currentNeuron->foodReaction->up = randSynapse(generator);
                tempLayer->currentNeuron->foodReaction->down = randSynapse(generator);
                tempLayer->currentNeuron->foodReaction->left = randSynapse(generator);
                tempLayer->currentNeuron->foodReaction->right = randSynapse(generator);

                tempLayer->currentNeuron->wallReaction->up = randSynapse(generator);
                tempLayer->currentNeuron->wallReaction->down = randSynapse(generator);
                tempLayer->currentNeuron->wallReaction->left = randSynapse(generator);
                tempLayer->currentNeuron->wallReaction->right = randSynapse(generator);
            } else if (randChance < 50) {
                tempLayer->currentNeuron->foodReaction->up = layerParentOne->currentNeuron->foodReaction->up;
                tempLayer->currentNeuron->foodReaction->down = layerParentOne->currentNeuron->foodReaction->down;
                tempLayer->currentNeuron->foodReaction->left = layerParentOne->currentNeuron->foodReaction->left;
                tempLayer->currentNeuron->foodReaction->right = layerParentOne->currentNeuron->foodReaction->right;

                tempLayer->currentNeuron->wallReaction->up = layerParentOne->currentNeuron->wallReaction->up;
                tempLayer->currentNeuron->wallReaction->down = layerParentOne->currentNeuron->wallReaction->down;
                tempLayer->currentNeuron->wallReaction->left = layerParentOne->currentNeuron->wallReaction->left;
                tempLayer->currentNeuron->wallReaction->right = layerParentOne->currentNeuron->wallReaction->right;
            } else {
                tempLayer->currentNeuron->foodReaction->up = layerParentTwo->currentNeuron->foodReaction->up;
                tempLayer->currentNeuron->foodReaction->down = layerParentTwo->currentNeuron->foodReaction->down;
                tempLayer->currentNeuron->foodReaction->left = layerParentTwo->currentNeuron->foodReaction->left;
                tempLayer->currentNeuron->foodReaction->right = layerParentTwo->currentNeuron->foodReaction->right;

                tempLayer->currentNeuron->wallReaction->up = layerParentTwo->currentNeuron->wallReaction->up;
                tempLayer->currentNeuron->wallReaction->down = layerParentTwo->currentNeuron->wallReaction->down;
                tempLayer->currentNeuron->wallReaction->left = layerParentTwo->currentNeuron->wallReaction->left;
                tempLayer->currentNeuron->wallReaction->right = layerParentTwo->currentNeuron->wallReaction->right;
            }
            tempLayer = tempLayer->nextNeuron;
            layerParentOne = layerParentOne->nextNeuron;
            layerParentTwo = layerParentTwo->nextNeuron;
            neuron++;
        }
        layersListTmp = layersListTmp->nextLayer; 
        layersListParentOne = layersListParentOne->nextLayer;
        layersListParentTwo = layersListParentTwo->nextLayer;
        layer++;
    }
}


void StraightNetwork::tests()
{
   /* #ifdef LOGS
        std::ofstream useMindOutput;
        useMindOutput.open("logs/useMindOutput.txt");

        field.initField(
            evolutionParameters.currentFieldSizeX,
            evolutionParameters.currentFieldSizeY,
            evolutionParameters.fullFieldSizeX,
            evolutionParameters.fullFieldSizeY
        );
        field.initEvoField();

        testNetwork();
        useMindOutput << useMind(field, 15, 15) << " OUTPUT " << std::endl;
        useMindOutput.close();
    #endif*/
}


void StraightNetwork::deleteNetwork()
{
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