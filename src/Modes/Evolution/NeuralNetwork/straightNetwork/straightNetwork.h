#ifndef STRAIGHT_NETWROK_H
#define STRAIGHT_NETWROK_H

#include <fstream>
#include <iostream>
#include "straightNeuron.h"
#include <Evolution/Field/evoField.h>
#include <NeuralNetwork/network.h>

class StraightNetwork : public Network
{
    public:
        StraightNetwork();
        void deleteNetwork();
        bool test = true;

        #ifdef LOGS
            EvoField field;
        #endif
        
        int useMind(EvoField evoField, int headX, int headY);

        struct NeuronsList {
            StraightNeuron currentNeuron;
            struct NeuronsList *nextNeuron; 
        };
        NeuronsList* firstLayer;
        NeuronsList* lastLayer;
        NeuronsList* tempLayer;
        NeuronsList* tempSecondLayer;
        NeuronsList* nextLayer;
        NeuronsList* outputLayer;
        StraightNeuron* lastNeuron;

        NeuronsList *layerParentOne;
        NeuronsList *layerParentTwo;

        struct  LayersList {
            int layerId;
            NeuronsList currentNeuronsList;
            struct LayersList *nextLayer;
        };
        LayersList* layersList;
        LayersList* layersListTmp;
        LayersList* layersListSecondTmp;
        LayersList* layersListParentOne;
        LayersList* layersListParentTwo;


        void mergeNetworks(struct LayersList *parentOne, struct LayersList *parentTwo);


        float randFloat;


        void tests();

    private:
        void initNetwork();
        void initLayers();
        void initNeurons();
        void neuronActivity();
        void testNetwork();

};

#endif