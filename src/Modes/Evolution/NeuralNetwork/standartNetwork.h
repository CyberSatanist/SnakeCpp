#ifndef STANDART_NETWROK_H
#define STANDART_NETWORK_H

#include <fstream>
#include <iostream>
#include "standartNeuron.h"
#include <Evolution/Field/evoField.h>

class StandartNetwork
{
    public:
        StandartNetwork();
        EvoField field;
        float useMind(EvoField evoField, int headX, int headY);
        void mergeNetworks(StandartNetwork *parentOne, StandartNetwork *parentTwo);

        struct NeuronsList {
            StandartNeuron currentNeuron;
            struct NeuronsList *nextNeuron; 
        };
        NeuronsList* firstLayer = new NeuronsList;
        NeuronsList* lastLayer = new NeuronsList;
        NeuronsList* tempLayer = new NeuronsList;
        NeuronsList* nextLayer = new NeuronsList;
        NeuronsList* outputLayer = new NeuronsList;

        NeuronsList *layerParentOne;
        NeuronsList *layerParentTwo;

        struct  LayersList {
            int layerId;
            NeuronsList currentNeuronsList;
            struct LayersList *nextLayer;
        };
        LayersList* layersList = new LayersList;
        LayersList* layersListTmp = new LayersList;
        LayersList* layersListParentOne = new LayersList;
        LayersList* layersListParentTwo = new LayersList;


        float randFloat;

    private:
        void initNetwork();
        void initLayers();
        void initNeurons();
        void neuronActivity();
        void testNetwork();

};

#endif