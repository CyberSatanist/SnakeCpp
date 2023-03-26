#ifndef STANDART_NETWROK_H
#define STANDART_NETWORK_H

#include "Evolution/Field/evoField.h"
#include "Evolution/Parameters/evolutionParameters.h"

extern EvolutionParameters evolutionParameters;

class StandartNetwork
{
    float *inputLayer;
    float **hiddenLayers;
    float *outputLayer;


    public:
        StandartNetwork();
        ~StandartNetwork();

        int useMind(EvoField &evoField, int headX, int headY);
        void mergeNetworks(StandartNetwork *parentOne, StandartNetwork *parentTwo);



    private:
        void initNetwork();
        void initLayer(float *layer, int neuronsCount);
        int neuronActivity();
        float* sumVectors(float *firstVector, int firstVectorSize, float *secondVector, int secondVectorSize);
  
};

#endif