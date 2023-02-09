#ifndef SIMPLE_NETWROK_H
#define SIMPLE_NETWROK_H

#include "Evolution/Field/evoField.h"
#include "NeuralNetwork/network.h"

class SimpleNetwork : public Network
{
    float *foodNeurons;
    float *wallNeurons;

    public:
        SimpleNetwork();
        ~SimpleNetwork();
        
        int useMind(EvoField &evoField, int headX, int headY);
        void mergeNetworks(SimpleNetwork *parentOne, SimpleNetwork *parentTwo);

        //Save-load
        void saveNetwork() {};
        void loadNetwork() {};
        

    private:
        int neuronActivity(float result);
        float validateResult(float result, float weight);

};

#endif