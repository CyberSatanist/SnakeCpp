#include "standartNetwork.h"
#include <Evolution/Parameters/evolutionParameters.h>
#include <random>
#include <math.h>

extern EvolutionParameters evolutionParameters;

StandartNetwork::StandartNetwork()
{
    field.initField(
        evolutionParameters.currentFieldSizeX,
        evolutionParameters.currentFieldSizeY,
        evolutionParameters.fullFieldSizeX,
        evolutionParameters.fullFieldSizeY
    );
    field.initEvoField();

    //test.open("test.txt");
    initNetwork();
    initLayers();
    initNeurons();
    testNetwork();
    //useMind(field, 15, 15);
    //test <<"OUTPUT IS " << useMind(field, 15, 15) << std::endl;

    //test.close();
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
 //   test << "Neuron Id" << tempLayer->currentNeuron.neuronId <<  std::endl;

    for (int neuronCount = 0; neuronCount < evolutionParameters.firstLayerNeuronCount; neuronCount++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
  //      test << "Neuron Id" << tempLayer->currentNeuron.neuronId <<  std::endl;
        tempLayer->nextNeuron = NULL;
    }



////HIDDEN LAYERS
    layersListTmp = layersListTmp->nextLayer;
    tempLayer = &(layersListTmp->currentNeuronsList);

 //   test << "Neuron Id" << tempLayer->currentNeuron.neuronId <<  std::endl;
    tempLayer->nextNeuron = NULL;

    for (int layerCount = 0; layerCount < evolutionParameters.countOfLayers; layerCount++) {
        tempLayer = &(layersListTmp->currentNeuronsList);
        for (int count = 0; count < evolutionParameters.countOfNeuronsInLayer; count++) {

            tempLayer->nextNeuron = new NeuronsList;
            tempLayer = tempLayer->nextNeuron;
 //           test << "Neuron Id" << tempLayer->currentNeuron.neuronId <<  std::endl;
            tempLayer->nextNeuron = NULL;
        }
        layersListTmp = layersListTmp->nextLayer;
    }


/////LAST LAYER
    tempLayer = &(layersListTmp->currentNeuronsList);
//    test << "Neuron Id" << tempLayer->currentNeuron.neuronId <<  std::endl;
    for (int neuronCount = 0; neuronCount < evolutionParameters.lastLayerNeuronCount; neuronCount++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
  //      test << "Neuron Id" << tempLayer->currentNeuron.neuronId <<  std::endl;
        tempLayer->nextNeuron = NULL;
    }


/////OUTPUT LAYER
    layersListTmp = layersListTmp->nextLayer;
    tempLayer = &(layersListTmp->currentNeuronsList);

    for (int neuronCount = 0; neuronCount < evolutionParameters.outputLayerNeuronCount; neuronCount++){
        tempLayer->nextNeuron = new NeuronsList;
        tempLayer = tempLayer->nextNeuron;
   //     test << "Neuron Id" << tempLayer->currentNeuron.neuronId <<  std::endl;
        tempLayer->nextNeuron = NULL;
    }
}


void StandartNetwork::initNeurons()
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> randGen(-10, 10);

    layersListTmp = layersList;
    while(layersListTmp->nextLayer){
        tempLayer = &(layersListTmp->currentNeuronsList);
        //test << "TEST1--" << tempLayer->currentNeuron.neuronId << std::endl;

        while (tempLayer->nextNeuron){
            tempLayer->currentNeuron.tmpConnection = new StandartNeuron::Connections;
            tempLayer->currentNeuron.firstConnection = tempLayer->currentNeuron.tmpConnection;
            nextLayer = &(layersListTmp->nextLayer->currentNeuronsList);

  //          test << "NEXT HOST NEURON " << tempLayer->currentNeuron.neuronId << std::endl;
            while(nextLayer->nextNeuron){
                randFloat = randGen(generator);
                randFloat = randFloat / 10;
                tempLayer->currentNeuron.tmpConnection->synapse = randFloat;
   //             test << "SYNAPSE NEURON ID  " << nextLayer->currentNeuron.neuronId <<  std::endl;
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
}


void StandartNetwork::testNetwork()
{
 /*   std::ofstream file;
    file.open("neuronTest.txt");
    if (file.is_open())
    {
        layersListTmp = layersList;
        while(layersListTmp){
            file << "\nLayer #" <<  layersListTmp->layerId << ";" << std::endl;

            tempLayer = &(layersListTmp->currentNeuronsList);
            while (tempLayer->nextNeuron){
                file << "- - Neuron #" <<  tempLayer->currentNeuron.neuronId << std::endl;
                file << "- - - Connected to:" << std::endl;
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.firstConnection;
                while (tempLayer->currentNeuron.tmpConnection->nextConnection){
                    file << "- - - - - - - Neuron #" <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                    file << "- - - - - - - - - - - Synapse: " <<  tempLayer->currentNeuron.tmpConnection->synapse << std::endl;
                    tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
                }
                tempLayer = tempLayer->nextNeuron;
            }
            layersListTmp = layersListTmp->nextLayer; 
        }
    }
    file.close();*/
}



float StandartNetwork::useMind(EvoField evoField, int headX, int headY)
{
    int radius = (sqrt(evolutionParameters.firstLayerNeuronCount) -1) / 2;

    tempLayer = &(layersList->currentNeuronsList);
    int count = 1;
    for (int countX = (headX - radius); countX <= (headX + radius); countX++){
        for (int countY = (headY - radius); countY <= (headY + radius); countY++){
            //test << "X  " << countX << "  Y  " << countY << "  count  " << count <<  std::endl;
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
            }
            count++;
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
              //  test << "=== INPUT BEFOR === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                tempLayer->currentNeuron.tmpConnection->currentNeuron->input = tempLayer->currentNeuron.input + tempLayer->currentNeuron.tmpConnection->synapse;
                if (tempLayer->currentNeuron.tmpConnection->currentNeuron->input > 0.9){
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->input =  tempLayer->currentNeuron.tmpConnection->currentNeuron->input - ((tempLayer->currentNeuron.tmpConnection->currentNeuron->input - 1.0) + 0.1);
                } else if (tempLayer->currentNeuron.tmpConnection->currentNeuron->input < -0.9){
                    tempLayer->currentNeuron.tmpConnection->currentNeuron->input =  tempLayer->currentNeuron.tmpConnection->currentNeuron->input - ((tempLayer->currentNeuron.tmpConnection->currentNeuron->input + 1.0) - 0.1);
                }
               //test << "=== NEURON  ID === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->neuronId << std::endl;
                //test << "=== INPUT AFTER === " <<  tempLayer->currentNeuron.tmpConnection->currentNeuron->input << std::endl;
                tempLayer->currentNeuron.tmpConnection = tempLayer->currentNeuron.tmpConnection->nextConnection;
            }
            tempLayer = tempLayer->nextNeuron;
        }
        layersListTmp = layersListTmp->nextLayer; 
    }
}