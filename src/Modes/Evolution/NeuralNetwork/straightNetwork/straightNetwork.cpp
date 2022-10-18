#include "straightNetwork.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>
#include <math.h>

extern EvolutionParameters evolutionParameters;

StraightNetwork::StraightNetwork()
{
    initNetwork();
    initLayers();
    initNeurons();
}


void StraightNetwork::initNetwork()
{
    layersList = new LayersList;
    layersListTmp = layersList;

    firstLayer = new NeuronsList;
    layersListTmp->currentNeuronsList = *firstLayer;
    layersListTmp->layerId = evolutionParameters.layerIdCounter;
    evolutionParameters.layerIdCounter++;
/*
    for (int count = 0; count < evolutionParameters.countOfLayers; count++) {
        layersListTmp->nextLayer = new LayersList;
        layersListTmp = layersListTmp->nextLayer;

        tempLayer = new NeuronsList;
        layersListTmp->currentNeuronsList = *tempLayer;
        layersListTmp->layerId = evolutionParameters.layerIdCounter;
        evolutionParameters.layerIdCounter++;
        layersListTmp->nextLayer = NULL;
    }
*/
    layersListTmp->nextLayer = new LayersList;
    layersListTmp = layersListTmp->nextLayer;
    layersListTmp->layerId = evolutionParameters.layerIdCounter;
    evolutionParameters.layerIdCounter++;

    lastLayer = new NeuronsList;
    layersListTmp->currentNeuronsList = *lastLayer;
    layersListTmp->nextLayer = NULL;
}


void StraightNetwork::initLayers()
{
    layersListTmp = layersList;

////FIRST LAYER
    tempLayer = &(layersListTmp->currentNeuronsList);

    for (int neuronCount = 0; neuronCount < evolutionParameters.firstLayerNeuronCount; neuronCount++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
        tempLayer->nextNeuron = NULL;
    }


/*
////HIDDEN LAYERS
    layersListTmp = layersListTmp->nextLayer;
    tempLayer = &(layersListTmp->currentNeuronsList);

    tempLayer->nextNeuron = NULL;

    for (int layerCount = 0; layerCount < evolutionParameters.countOfLayers; layerCount++) {
        tempLayer = &(layersListTmp->currentNeuronsList);
        for (int count = 0; count < evolutionParameters.countOfNeuronsInLayer; count++) {

            tempLayer->nextNeuron = new NeuronsList;
            tempLayer = tempLayer->nextNeuron;
            tempLayer->nextNeuron = NULL;
        }
        layersListTmp = layersListTmp->nextLayer;
    }
*/

/////LAST LAYER
    layersListTmp = layersListTmp->nextLayer;
    layersListTmp->nextLayer = NULL;
    tempLayer = &(layersListTmp->currentNeuronsList);
    for (int neuronCount = 0; neuronCount < evolutionParameters.lastLayerNeuronCount; neuronCount++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
        lastNeuron = &(tempLayer->currentNeuron);
        tempLayer->nextNeuron = NULL;
    }
}


void StraightNetwork::initNeurons()
{
    layersListTmp = layersList;
    while(layersListTmp){
        tempLayer = &(layersListTmp->currentNeuronsList);

        while (tempLayer->nextNeuron){
            tempLayer->currentNeuron.tmpConnection = new StraightNeuron::Connections;
            tempLayer->currentNeuron.tmpConnection->nextConnection = NULL;
            tempLayer->currentNeuron.firstConnection = tempLayer->currentNeuron.tmpConnection;
            if (layersListTmp->nextLayer){
                nextLayer = &(layersListTmp->nextLayer->currentNeuronsList);
                while(nextLayer->nextNeuron){
                    tempLayer->currentNeuron.tmpConnection->currentNeuron = &(nextLayer->currentNeuron);
                    tempLayer->currentNeuron.tmpConnection->nextConnection = new StraightNeuron::Connections;
                    tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
                    tempLayer->currentNeuron.tmpConnection->nextConnection = NULL;
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

    tempLayer = &(layersList->currentNeuronsList);
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
                        tempLayer->currentNeuron.input = 1; //1.0
                        break;
                    case Field::Free:
                        tempLayer->currentNeuron.input = 0;//0.33
                        break;
                    case Field::Snake:
                        tempLayer->currentNeuron.input = -1; //-0.33
                    break;
                    case Field::Wall:
                        tempLayer->currentNeuron.input = -1; //-1.0
                    break;
                }
            } else {
                tempLayer->currentNeuron.input = -1; 
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
    #ifdef LOGS
        std::ofstream neuronActivity;
        neuronActivity.open("logs/neuronActivity.txt");
    #endif
    layersListTmp = layersList;
    tempLayer = &(layersListTmp->currentNeuronsList);
    while (tempLayer->nextNeuron){
        tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.firstConnection;
        while (tempLayer->currentNeuron.tmpConnection->nextConnection){
            switch (tempLayer->currentNeuron.input) {
                case -1:
                    #ifdef LOGS
                        neuronActivity << "BEFOR    |    WALL" << std::endl;
                        neuronActivity << "NEURON ID " << tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right<< std::endl;
                    #endif
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up += tempLayer->currentNeuron.wallReaction->up;
                    if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up > 100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up = 100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up - 100);
                    } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up < -100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up = -100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up + 100);
                    }
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down += tempLayer->currentNeuron.wallReaction->down;
                    if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down > 100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down = 100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down - 100);
                    } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down < -100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down = -100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down + 100);
                    }
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left += tempLayer->currentNeuron.wallReaction->left;
                    if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left > 100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left = 100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left - 100);
                    } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left < -100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left = -100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left + 100);
                    }
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right += tempLayer->currentNeuron.wallReaction->right;
                    if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right > 100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right = 100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right - 100);
                    } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right < -100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right = -100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right + 100);
                    }
                    #ifdef LOGS
                        neuronActivity << "AFTER" << std::endl;
                        neuronActivity << "NEURON ID " << tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up<< std::endl;                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right<< std::endl;
                        neuronActivity << "   " << std::endl;
                    #endif
                    break;
                case 1:
                    #ifdef LOGS
                        neuronActivity << "BEFOR    |    FOOD" << std::endl;
                        neuronActivity << "NEURON ID " << tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up<< std::endl;                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right<< std::endl;
                    #endif
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up += tempLayer->currentNeuron.foodReaction->up;
                    if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up > 100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up = 100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up - 100);
                    } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up < -100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up = -100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up + 100);
                    }
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down += tempLayer->currentNeuron.foodReaction->down;
                    if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down > 100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down = 100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down - 100);
                    } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down < -100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down = -100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down + 100);
                    }
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left += tempLayer->currentNeuron.foodReaction->left;
                    if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left > 100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left = 100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left - 100);
                    } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left < -100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left = -100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left + 100);
                    }
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right += tempLayer->currentNeuron.foodReaction->right;
                    if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right > 100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right = 100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right - 100);
                    } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right < -100){
                        tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right = -100 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right + 100);
                    }
                    #ifdef LOGS
                        neuronActivity << "AFTER" << std::endl;
                        neuronActivity << "NEURON ID " << tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up<< std::endl;                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->up<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->down<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->left<< std::endl;
                        neuronActivity << tempLayer->currentNeuron.tmpConnection->currentNeuron->resultReaction->right<< std::endl;
                        neuronActivity << "   " << std::endl;
                    #endif
                    break;
            }
            tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
        }
        tempLayer = tempLayer->nextNeuron;
    }

    layersListTmp = layersListTmp->nextLayer;
    tempLayer = &(layersListTmp->currentNeuronsList);

    for (int neuronCount = 0; neuronCount < (evolutionParameters.lastLayerNeuronCount - 1); neuronCount++){
        lastNeuron->resultReaction->up += tempLayer->currentNeuron.resultReaction->up;
        if (lastNeuron->resultReaction->up > 100) {
            lastNeuron->resultReaction->up = 100 - (lastNeuron->resultReaction->up - 100);
        } else if (lastNeuron->resultReaction->up < -100) {
            lastNeuron->resultReaction->up = -100 - (lastNeuron->resultReaction->up + 100);
        }
        lastNeuron->resultReaction->down += tempLayer->currentNeuron.resultReaction->down;
        if (lastNeuron->resultReaction->down > 100) {
            lastNeuron->resultReaction->down = 100 - (lastNeuron->resultReaction->down - 100);
        } else if (lastNeuron->resultReaction->down < -100) {
            lastNeuron->resultReaction->down = -100 - (lastNeuron->resultReaction->down + 100);
        }
        lastNeuron->resultReaction->left += tempLayer->currentNeuron.resultReaction->left;
        if (lastNeuron->resultReaction->left > 100) {
            lastNeuron->resultReaction->left = 100 - (lastNeuron->resultReaction->left - 100);
        } else if (lastNeuron->resultReaction->left < -100) {
            lastNeuron->resultReaction->left = -100 - (lastNeuron->resultReaction->left + 100);
        }
        lastNeuron->resultReaction->right += tempLayer->currentNeuron.resultReaction->right;
        if (lastNeuron->resultReaction->right > 100) {
            lastNeuron->resultReaction->right = 100 - (lastNeuron->resultReaction->right - 100);
        } else if (lastNeuron->resultReaction->right < -100) {
            lastNeuron->resultReaction->right = -100 - (lastNeuron->resultReaction->right + 100);
        }
        tempLayer = tempLayer->nextNeuron;
    }


    #ifdef LOGS
        neuronActivity.close();
    #endif
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
    #ifdef LOGS
        std::ofstream mergeTest;
        mergeTest.open("logs/mergeTest.txt");
    #endif
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
        tempLayer = &(layersListTmp->currentNeuronsList);
        layerParentOne = &(layersListParentOne->currentNeuronsList);
        layerParentTwo = &(layersListParentTwo->currentNeuronsList);
        while (tempLayer->nextNeuron){
            #ifdef LOGS
                mergeTest << "PARENT" << std::endl;
                mergeTest << "NEURON ID " << layerParentOne->currentNeuron.neuronId << std::endl;
                mergeTest << "FOOD" << std::endl;
                mergeTest << layerParentOne->currentNeuron.foodReaction->up<< std::endl;
                mergeTest << layerParentOne->currentNeuron.foodReaction->down<< std::endl;
                mergeTest << layerParentOne->currentNeuron.foodReaction->left<< std::endl;
                mergeTest << layerParentOne->currentNeuron.foodReaction->right<< std::endl;
                mergeTest << "WALL" << std::endl;
                mergeTest << layerParentOne->currentNeuron.wallReaction->up<< std::endl;
                mergeTest << layerParentOne->currentNeuron.wallReaction->down<< std::endl;
                mergeTest << layerParentOne->currentNeuron.wallReaction->left<< std::endl;
                mergeTest << layerParentOne->currentNeuron.wallReaction->right<< std::endl;
                mergeTest << "+++" << std::endl;
                mergeTest << "BEFOR" << std::endl;
                mergeTest << neuron << std::endl;
                mergeTest << "FOOD" << std::endl;
                mergeTest << tempLayer->currentNeuron.foodReaction->up<< std::endl;
                mergeTest << tempLayer->currentNeuron.foodReaction->down<< std::endl;
                mergeTest << tempLayer->currentNeuron.foodReaction->left<< std::endl;
                mergeTest << tempLayer->currentNeuron.foodReaction->right<< std::endl;
                mergeTest << "WALL" << std::endl;
                mergeTest << tempLayer->currentNeuron.wallReaction->up<< std::endl;
                mergeTest << tempLayer->currentNeuron.wallReaction->down<< std::endl;
                mergeTest << tempLayer->currentNeuron.wallReaction->left<< std::endl;
                mergeTest << tempLayer->currentNeuron.wallReaction->right<< std::endl;
            #endif
            randChance = randGen(generator);
            if ((randChance < (evolutionParameters.mutationChance / 2)) | (randChance >  (100 -evolutionParameters.mutationChance))){
                tempLayer->currentNeuron.foodReaction->up = randSynapse(generator);
                tempLayer->currentNeuron.foodReaction->down = randSynapse(generator);
                tempLayer->currentNeuron.foodReaction->left = randSynapse(generator);
                tempLayer->currentNeuron.foodReaction->right = randSynapse(generator);

                tempLayer->currentNeuron.wallReaction->up = randSynapse(generator);
                tempLayer->currentNeuron.wallReaction->down = randSynapse(generator);
                tempLayer->currentNeuron.wallReaction->left = randSynapse(generator);
                tempLayer->currentNeuron.wallReaction->right = randSynapse(generator);
            } else if (randChance < 50) {
                tempLayer->currentNeuron.foodReaction->up = layerParentOne->currentNeuron.foodReaction->up;
                tempLayer->currentNeuron.foodReaction->down = layerParentOne->currentNeuron.foodReaction->down;
                tempLayer->currentNeuron.foodReaction->left = layerParentOne->currentNeuron.foodReaction->left;
                tempLayer->currentNeuron.foodReaction->right = layerParentOne->currentNeuron.foodReaction->right;

                tempLayer->currentNeuron.wallReaction->up = layerParentOne->currentNeuron.wallReaction->up;
                tempLayer->currentNeuron.wallReaction->down = layerParentOne->currentNeuron.wallReaction->down;
                tempLayer->currentNeuron.wallReaction->left = layerParentOne->currentNeuron.wallReaction->left;
                tempLayer->currentNeuron.wallReaction->right = layerParentOne->currentNeuron.wallReaction->right;
            } else {
                tempLayer->currentNeuron.foodReaction->up = layerParentTwo->currentNeuron.foodReaction->up;
                tempLayer->currentNeuron.foodReaction->down = layerParentTwo->currentNeuron.foodReaction->down;
                tempLayer->currentNeuron.foodReaction->left = layerParentTwo->currentNeuron.foodReaction->left;
                tempLayer->currentNeuron.foodReaction->right = layerParentTwo->currentNeuron.foodReaction->right;

                tempLayer->currentNeuron.wallReaction->up = layerParentTwo->currentNeuron.wallReaction->up;
                tempLayer->currentNeuron.wallReaction->down = layerParentTwo->currentNeuron.wallReaction->down;
                tempLayer->currentNeuron.wallReaction->left = layerParentTwo->currentNeuron.wallReaction->left;
                tempLayer->currentNeuron.wallReaction->right = layerParentTwo->currentNeuron.wallReaction->right;
            } 
            #ifdef LOGS
                mergeTest << "AFTER" << std::endl;
                mergeTest << "NEURON ID " << tempLayer->currentNeuron.neuronId << std::endl;
                mergeTest << "FOOD" << std::endl;
                mergeTest << tempLayer->currentNeuron.foodReaction->up<< std::endl;
                mergeTest << tempLayer->currentNeuron.foodReaction->down<< std::endl;
                mergeTest << tempLayer->currentNeuron.foodReaction->left<< std::endl;
                mergeTest << tempLayer->currentNeuron.foodReaction->right<< std::endl;
                mergeTest << "WALL" << std::endl;
                mergeTest << tempLayer->currentNeuron.wallReaction->up<< std::endl;
                mergeTest << tempLayer->currentNeuron.wallReaction->down<< std::endl;
                mergeTest << tempLayer->currentNeuron.wallReaction->left<< std::endl;
                mergeTest << tempLayer->currentNeuron.wallReaction->right<< std::endl;
                mergeTest << "   " << std::endl;
            #endif
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
    delete layersListParentOne;
    delete layersListParentTwo;
    delete layerParentOne;
    //delete layerParentTwo;
    #ifdef LOGS
        mergeTest.close();
    #endif
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
    while(layersListTmp->nextLayer){
        tempLayer = &(layersListTmp->currentNeuronsList);
        while (tempLayer->nextNeuron){
            tempLayer->currentNeuron.deleteNeuron();
            tempLayer = tempLayer->nextNeuron;
        }
        tempLayer->currentNeuron.deleteNeuron();
        delete tempLayer;

        layersListSecondTmp = layersListTmp;
        layersListTmp = layersListTmp->nextLayer;
        delete layersListSecondTmp->nextLayer;
        delete layersListSecondTmp;
    }
    delete firstLayer;
    delete lastLayer;
    delete nextLayer;
}