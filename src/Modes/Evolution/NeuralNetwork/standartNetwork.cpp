#include "standartNetwork.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>
#include <math.h>

extern EvolutionParameters evolutionParameters;

StandartNetwork::StandartNetwork()
{
    #ifdef LOGS
    field.initField(
        evolutionParameters.currentFieldSizeX,
        evolutionParameters.currentFieldSizeY,
        evolutionParameters.fullFieldSizeX,
        evolutionParameters.fullFieldSizeY
    );
    field.initEvoField();

    test.open("test.txt");
    #endif

    initNetwork();
    initLayers();
    initNeurons();

    #ifdef LOGS
    testNetwork();
    test << useMind(field, 15, 15) << " OUTPUT " << std::endl;
    test.close();
    #endif
}


void StandartNetwork::initNetwork()
{
    layersListTmp = layersList;
    layersListTmp->currentNeuronsList = *firstLayer;
    layersListTmp->layerId = evolutionParameters.layerIdCounter;
    evolutionParameters.layerIdCounter++;
    layersListTmp->nextLayer = NULL;

    for (int count = 0; count < evolutionParameters.countOfLayers; count++) {
        NeuronsList* tempLayer = new NeuronsList;
        layersListTmp->nextLayer = new LayersList;
        layersListTmp = layersListTmp->nextLayer;
        layersListTmp->currentNeuronsList = *tempLayer;
        layersListTmp->layerId = evolutionParameters.layerIdCounter;
        evolutionParameters.layerIdCounter++;
        layersListTmp->nextLayer = NULL;
    }

    layersListTmp->nextLayer = new LayersList;
    layersListTmp = layersListTmp->nextLayer;
    layersListTmp->layerId = evolutionParameters.layerIdCounter;
    evolutionParameters.layerIdCounter++;
    layersListTmp->currentNeuronsList = *lastLayer;
    for (int count = 0; count < evolutionParameters.lastLayerNeuronCount; count++) {
    
    }

    layersListTmp->nextLayer = new LayersList;
    layersListTmp = layersListTmp->nextLayer;
    layersListTmp->layerId = evolutionParameters.layerIdCounter;
    evolutionParameters.layerIdCounter++;
    layersListTmp->currentNeuronsList = *outputLayer;
    layersListTmp->nextLayer = NULL;
    for (int count = 0; count < evolutionParameters.outputLayerNeuronCount; count++) {
    
    }
}


void StandartNetwork::initLayers()
{
    layersListTmp = layersList;

////FIRST LAYER
    tempLayer = &(layersListTmp->currentNeuronsList);

    for (int neuronCount = 0; neuronCount < evolutionParameters.firstLayerNeuronCount; neuronCount++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
        tempLayer->nextNeuron = NULL;
    }



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


/////LAST LAYER
    tempLayer = &(layersListTmp->currentNeuronsList);
    for (int neuronCount = 0; neuronCount < evolutionParameters.lastLayerNeuronCount; neuronCount++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
        tempLayer->nextNeuron = NULL;
    }


/////OUTPUT LAYER
    layersListTmp = layersListTmp->nextLayer;
    tempLayer = &(layersListTmp->currentNeuronsList);

    for (int neuronCount = 0; neuronCount < evolutionParameters.outputLayerNeuronCount; neuronCount++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
        tempLayer->nextNeuron = NULL;
    }
}


void StandartNetwork::initNeurons()
{
    #ifdef LOGS
    std::ofstream test;
    test.open("test.txt");
    #endif

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(-10, 10);

    layersListTmp = layersList;
    while(layersListTmp->nextLayer){
        tempLayer = &(layersListTmp->currentNeuronsList);

        while (tempLayer->nextNeuron){
            tempLayer->currentNeuron.tmpConnection = new StandartNeuron::Connections;
            tempLayer->currentNeuron.firstConnection = tempLayer->currentNeuron.tmpConnection;
            nextLayer = &(layersListTmp->nextLayer->currentNeuronsList);

            #ifdef LOGS
            test << "NEXT HOST NEURON " << tempLayer->currentNeuron.neuronId << std::endl;
            #endif

            while(nextLayer->nextNeuron){
                randFloat = randGen(generator);
                randFloat = randFloat / 10;
                tempLayer->currentNeuron.tmpConnection->synapse = randFloat;
                
                #ifdef LOGS
                test << "SYNAPSE NEURON ID  " << nextLayer->currentNeuron.neuronId <<  std::endl;
                #endif

                tempLayer->currentNeuron.tmpConnection->currentNeuron = &(nextLayer->currentNeuron);
                tempLayer->currentNeuron.tmpConnection->nextConnection = new StandartNeuron::Connections;
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
                tempLayer->currentNeuron.tmpConnection->nextConnection = NULL;
                nextLayer = nextLayer->nextNeuron;
            }
            tempLayer = tempLayer->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
    }
    #ifdef LOGS
    test.close();
    #endif
}


void StandartNetwork::testNetwork()
{
    #ifdef LOGS
        std::ofstream test;
        test.open("neuronTest.txt");
    #endif
    layersListTmp = layersList;
    while(layersListTmp){
        #ifdef LOGS
            test << "\nLayer #" <<  layersListTmp->layerId << ";" << std::endl;
        #endif
        tempLayer = &(layersListTmp->currentNeuronsList);
        while (tempLayer->nextNeuron){                
            #ifdef LOGS
                test << "- - Neuron #" <<  tempLayer->currentNeuron.neuronId << std::endl;
                test << "- - Input " <<  tempLayer->currentNeuron.input << std::endl;
                test << "- - - Connected to:" << std::endl;
            #endif
            tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.firstConnection;
            while (tempLayer->currentNeuron.tmpConnection->nextConnection){
                #ifdef LOGS
                    test << "- - - - - - - Neuron #" <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                    test << "- - - - - - - - - - - Synapse: " <<  tempLayer->currentNeuron.tmpConnection->synapse << std::endl;
                #endif
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
            }
            tempLayer = tempLayer->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
    }
    #ifdef LOGS
        test.close();
    #endif
}



float StandartNetwork::useMind(EvoField evoField, int headX, int headY)
{
    int radius = (sqrt(evolutionParameters.firstLayerNeuronCount) -1) / 2;

    tempLayer = &(layersList->currentNeuronsList);
    for (int countX = (headX - radius); countX <= (headX + radius); countX++){
        for (int countY = (headY - radius); countY <= (headY + radius); countY++){
            if (
                countX > evoField.currentBeginX & 
                countX < evoField.fullSizeX & 
                countY > evoField.currentBeginY & 
                countY < evoField.fullSizeY
            ) {
                switch (evoField.getCell(countX, countY)){
                    case Field::Food:
                        tempLayer->currentNeuron.input = 1.0; 
                        break;
                    case Field::Free:
                        tempLayer->currentNeuron.input = 0.33; 
                        break;
                    case Field::Snake:
                        tempLayer->currentNeuron.input = -0.33; 
                    break;
                    case Field::Wall:
                        tempLayer->currentNeuron.input = -1.0; 
                    break;
                }
            } else {
                tempLayer->currentNeuron.input = -1.0; 
            }
            tempLayer = tempLayer->nextNeuron;
        }
    }
    neuronActivity();

    layersListTmp = layersList;
    while(layersListTmp->nextLayer){
        layersListTmp = layersListTmp->nextLayer;
    }
    return layersListTmp->currentNeuronsList.currentNeuron.input;
}


void StandartNetwork::neuronActivity()
{
    layersListTmp = layersList;
    while(layersListTmp){
        tempLayer = &(layersListTmp->currentNeuronsList);
        while (tempLayer->nextNeuron){
            tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.firstConnection;
            while (tempLayer->currentNeuron.tmpConnection->nextConnection){
                #ifdef LOGS
                    test << "=== INPUT BEFOR === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                #endif
                tempLayer->currentNeuron.tmpConnection->currentNeuron->input = tempLayer->currentNeuron.input + tempLayer->currentNeuron.tmpConnection->synapse;
                if (tempLayer->currentNeuron.tmpConnection->currentNeuron->input > 0.9){
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->input =  tempLayer->currentNeuron.tmpConnection->currentNeuron->input - ((tempLayer->currentNeuron.tmpConnection->currentNeuron->input - 1.0) + 0.1);
                } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->input < -0.9){
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->input =  tempLayer->currentNeuron.tmpConnection->currentNeuron->input - ((tempLayer->currentNeuron.tmpConnection->currentNeuron->input + 1.0) - 0.1);
                }
                #ifdef LOGS
                    test << "=== NEURON  ID === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                    test << "=== INPUT AFTER === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                #endif
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
            }
            tempLayer = tempLayer->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
    }
}



void StandartNetwork::mergeNetworks(StandartNetwork *parentOne, StandartNetwork *parentTwo)
{
    #ifdef LOGS
        std::ofstream test;
        test.open("mergeTest.txt");
    #endif

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(0, 100);
    std::uniform_int_distribution<> randSynapse(-10, 10);
    int randChance;
    float randSyn;

    layersListTmp = layersList;
    #ifdef LOGS
        test << "HOST NEURON ID : " << layersListTmp->currentNeuronsList.currentNeuron.neuronId << std::endl;
    #endif
    layersListParentOne = parentOne->layersList;
    #ifdef LOGS
        test << "PARENT 1 NEURON ID : " << layersListParentOne->currentNeuronsList.currentNeuron.neuronId << std::endl;
    #endif
    layersListParentTwo = parentTwo->layersList;
    #ifdef LOGS
        test << "PARENT 2 NEURON ID : " << layersListParentTwo->currentNeuronsList.currentNeuron.neuronId << "\n" << std::endl;
    #endif
    while(layersListTmp->nextLayer){
        tempLayer = &(layersListTmp->currentNeuronsList);
        layerParentOne = &(layersListParentOne->currentNeuronsList);
        layerParentTwo = &(layersListParentTwo->currentNeuronsList);
        while (tempLayer->nextNeuron){
            tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.firstConnection;
            layerParentOne->currentNeuron.tmpConnection = layerParentOne->currentNeuron.firstConnection;
            layerParentTwo->currentNeuron.tmpConnection = layerParentTwo->currentNeuron.firstConnection;
            while (tempLayer->currentNeuron.tmpConnection->nextConnection){
                randChance = randGen(generator);
                #ifdef LOGS
                    test << "=== SYNAPSE BEFOR === " <<  tempLayer->currentNeuron.tmpConnection->synapse << std::endl;
                    test << "=== NEURON ID=== " <<  tempLayer->currentNeuron.neuronId << std::endl;
                    test << "=== CONNECTED TO ID=== " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                #endif
                if ((randChance < (evolutionParameters.mutationChance / 2)) | (randChance >  (100 -evolutionParameters.mutationChance))){
                    randSyn = randSynapse(generator);
                    #ifdef LOGS
                        test << "=== RANDOM SYNAPSE === " << randSyn << std::endl;                                  
                    #endif
                    tempLayer->currentNeuron.tmpConnection->synapse = randSyn / 10;
                } else if (randChance < 50) {
                    #ifdef LOGS
                        test << "=== PARENT 1 SYNAPSE === " <<  layerParentOne->currentNeuron.tmpConnection->synapse << std::endl;                       
                    #endif
                    tempLayer->currentNeuron.tmpConnection->synapse = layerParentOne->currentNeuron.tmpConnection->synapse;
                } else {
                    tempLayer->currentNeuron.tmpConnection->synapse = layerParentTwo->currentNeuron.tmpConnection->synapse;
                    #ifdef LOGS
                        test << "=== PARENT 2 SYNAPSE === " <<  layerParentOne->currentNeuron.tmpConnection->synapse << std::endl;                       
                    #endif
                }
                #ifdef LOGS
                    test << "=== SYNAPSE AFTER === " <<  tempLayer->currentNeuron.tmpConnection->synapse << "\n" << std::endl;
                    test << "=== INPUT BEFOR === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                    test << "=== NEURON  ID === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                    test << "=== INPUT AFTER === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                #endif
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
                layerParentOne->currentNeuron.tmpConnection = layerParentOne->currentNeuron.tmpConnection->nextConnection; 
                layerParentTwo->currentNeuron.tmpConnection = layerParentTwo->currentNeuron.tmpConnection->nextConnection;
            }
            tempLayer = tempLayer->nextNeuron;
            layerParentOne = layerParentOne->nextNeuron;
            layerParentTwo = layerParentTwo->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
        layersListParentOne = layersListParentOne->nextLayer;
        layersListParentTwo = layersListParentTwo->nextLayer;
    }
    #ifdef LOGS
        test.close();
    #endif
}