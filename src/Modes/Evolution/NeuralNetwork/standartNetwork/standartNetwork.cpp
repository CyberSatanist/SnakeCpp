#include "standartNetwork.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>
#include <math.h>

extern EvolutionParameters evolutionParameters;

StandartNetwork::StandartNetwork()
{
    initNetwork();
    initLayers();
    initNeurons();
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

    layersListTmp->nextLayer = new LayersList;
    layersListTmp = layersListTmp->nextLayer;
    layersListTmp->layerId = evolutionParameters.layerIdCounter;
    evolutionParameters.layerIdCounter = 0;
    layersListTmp->currentNeuronsList = *outputLayer;
    layersListTmp->nextLayer = NULL;
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
        std::ofstream initNeurons;
        initNeurons.open("logs/initNeurons.txt");
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
                initNeurons << "NEXT HOST NEURON " << tempLayer->currentNeuron.neuronId << std::endl;
            #endif

            while(nextLayer->nextNeuron){
                randFloat = randGen(generator);
                randFloat = randFloat / 10;
                tempLayer->currentNeuron.tmpConnection->synapse = randFloat;
                
                #ifdef LOGS
                    initNeurons << "SYNAPSE NEURON ID  " << nextLayer->currentNeuron.neuronId <<  std::endl;
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
        initNeurons.close();
    #endif
}


void StandartNetwork::testNetwork()
{
    #ifdef LOGS
        std::ofstream neuronTest;
        if (test){
            neuronTest.open("logs/neuronTestBefor.txt");
            neuronTest << "BEFOR" << std::endl;
        } else {
            neuronTest.open("logs/neuronTestAfter.txt");
            neuronTest << "AFTER" << std::endl;
        }
    #endif
    layersListTmp = layersList;
    while(layersListTmp){
        #ifdef LOGS
            neuronTest << "\nLayer #" <<  layersListTmp->layerId << ";" << std::endl;
        #endif
        tempLayer = &(layersListTmp->currentNeuronsList);
        while (tempLayer->nextNeuron){                
            #ifdef LOGS
                neuronTest << "- - Neuron #" <<  tempLayer->currentNeuron.neuronId << std::endl;
                neuronTest << "- - Input " <<  tempLayer->currentNeuron.input << std::endl;
                neuronTest << "- - - Connected to:" << std::endl;
            #endif
            tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.firstConnection;
            while (tempLayer->currentNeuron.tmpConnection->nextConnection){
                #ifdef LOGS
                    neuronTest << "- - - - - - - Neuron #" <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                    neuronTest << "- - - - - - - - - - - Synapse: " <<  tempLayer->currentNeuron.tmpConnection->synapse << std::endl;
                #endif
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
            }
            tempLayer = tempLayer->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
    }
    #ifdef LOGS
        neuronTest.close();
    #endif
}



float StandartNetwork::useMind(EvoField evoField, int headX, int headY)
{
    int radius = (sqrt(evolutionParameters.firstLayerNeuronCount) -1) / 2;

    tempLayer = &(layersList->currentNeuronsList);
    for (int countX = (headX - radius); countX <= (headX + radius); countX++){
        for (int countY = (headY - radius); countY <= (headY + radius); countY++){
            if (
                (countX > evoField.getCurrentBeginX()) && 
                (countX < evoField.getFullSizeX()) && 
                (countY > evoField.getCurrentBeginY()) && 
                (countY < evoField.getFullSizeY())
            ) {
                switch (evoField.getCell(countX, countY)){
                    case Field::Food:
                        tempLayer->currentNeuron.input = 0.9; //1.0
                        break;
                    case Field::Free:
                        tempLayer->currentNeuron.input = 0.3;//0.33
                        break;
                    case Field::Snake:
                        tempLayer->currentNeuron.input = -0.3; //-0.33
                    break;
                    case Field::Wall:
                        tempLayer->currentNeuron.input = -0.9; //-1.0
                    break;
                }
            } else {
                tempLayer->currentNeuron.input = -0.9; 
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
    #ifdef LOGS
        std::ofstream neuronActivity;
        neuronActivity.open("logs/neuronActivity.txt");
    #endif
    layersListTmp = layersList;
    while(layersListTmp){
        tempLayer = &(layersListTmp->currentNeuronsList);
        while (tempLayer->nextNeuron){
            tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.firstConnection;
            while (tempLayer->currentNeuron.tmpConnection->nextConnection){
                #ifdef LOGS
                    neuronActivity << "=== === INPUT === " <<  tempLayer->currentNeuron.input << std::endl;
                    neuronActivity << "=== === SYNAPSE === " <<  tempLayer->currentNeuron.tmpConnection->synapse << std::endl;
                    neuronActivity << "=== === CONNECTED NEURON  ID === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                    neuronActivity << "=== === INPUT BEFOR === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                #endif
                tempLayer->currentNeuron.tmpConnection->currentNeuron->input = tempLayer->currentNeuron.input + tempLayer->currentNeuron.tmpConnection->synapse;
                if (tempLayer->currentNeuron.tmpConnection->currentNeuron->input > 1.0){
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->input =  1.0 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->input - 1.0);
                } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->input < -1.0){
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->input =  -1.0 - (tempLayer->currentNeuron.tmpConnection->currentNeuron->input + 1.0);
                }
                #ifdef LOGS
                    neuronActivity << "=== === === INPUT AFTER === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << "\n" << std::endl;
                #endif
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
            }
            tempLayer = tempLayer->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
    }
    #ifdef LOGS
        neuronActivity.close();
    #endif
}



void StandartNetwork::mergeNetworks(LayersList *parentOne, LayersList *parentTwo)
{
    testNetwork();
    #ifdef LOGS
        std::ofstream mergeTest;
        mergeTest.open("logs/mergeTest.txt");
    #endif

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(0, 100);
    std::uniform_int_distribution<> randSynapse(-10, 10);
    int randChance;
    float randSyn;

    layersListTmp = layersList;
    #ifdef LOGS
        mergeTest << "HOST NEURON ID : " << layersListTmp->currentNeuronsList.currentNeuron.neuronId << std::endl;
    #endif

    layersListParentOne = parentOne;
    #ifdef LOGS
        mergeTest << "PARENT 1 NEURON ID : " << layersListParentOne->currentNeuronsList.currentNeuron.neuronId << std::endl;
    #endif

    layersListParentTwo = parentTwo;
    #ifdef LOGS
        mergeTest << "PARENT 2 NEURON ID : " << layersListParentTwo->currentNeuronsList.currentNeuron.neuronId << "\n" << std::endl;
    #endif
    int layer = 1;
    int neuron = 1;
    int connection = 1;
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
                    mergeTest << "=== SYNAPSE BEFOR === " <<  tempLayer->currentNeuron.tmpConnection->synapse << std::endl;
                    mergeTest << "=== NEURON ID=== " <<  tempLayer->currentNeuron.neuronId << std::endl;
                    mergeTest << "=== CONNECTED TO ID=== " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                #endif
                if ((randChance < (evolutionParameters.mutationChance / 2)) | (randChance >  (100 -evolutionParameters.mutationChance))){
                    randSyn = randSynapse(generator);
                    #ifdef LOGS
                        mergeTest << "=== RANDOM SYNAPSE === " << randSyn << std::endl;                                  
                    #endif
                    tempLayer->currentNeuron.tmpConnection->synapse = randSyn / 10;
                } else if (randChance < 50) {
                    #ifdef LOGS
                        mergeTest << "=== PARENT 1 ID === " <<  layerParentOne->currentNeuron.neuronId << std::endl;  
                        mergeTest << "=== PARENT 1 SYNAPSE === " <<  layerParentOne->currentNeuron.tmpConnection->synapse << std::endl;                      
                    #endif
                    tempLayer->currentNeuron.tmpConnection->synapse = layerParentOne->currentNeuron.tmpConnection->synapse;
                } else {
                    #ifdef LOGS
                        mergeTest << "=== PARENT 2 ID === " <<  layerParentTwo->currentNeuron.neuronId << std::endl;
                        mergeTest << "=== PARENT 2 SYNAPSE === " <<  layerParentTwo->currentNeuron.tmpConnection->synapse << std::endl;
                    #endif
                    tempLayer->currentNeuron.tmpConnection->synapse = layerParentTwo->currentNeuron.tmpConnection->synapse;
                    //tempLayer->currentNeuron.tmpConnection->synapse = layerParentOne->currentNeuron.tmpConnection->synapse;
                }   
                #ifdef LOGS
                    mergeTest << "=== SYNAPSE AFTER === " <<  tempLayer->currentNeuron.tmpConnection->synapse << "\n" << std::endl;
                    mergeTest << "=== INPUT BEFOR === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                    mergeTest << "=== NEURON  ID === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                    mergeTest << "=== INPUT AFTER === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                #endif
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection; 
                layerParentOne->currentNeuron.tmpConnection = layerParentOne->currentNeuron.tmpConnection->nextConnection;
                //layerParentTwo->currentNeuron.tmpConnection = layerParentTwo->currentNeuron.tmpConnection->nextConnection; 
                connection++;
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
    #ifdef LOGS
        mergeTest.close();
    #endif
    test = false;
    testNetwork();
}


void StandartNetwork::tests()
{
    #ifdef LOGSS
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
    #endif
}

void StandartNetwork::deleteNetwork()
{

}