#ifndef SIMPLE_NETWROK_H
#define SIMPLE_NETWROK_H

#include "Evolution/Field/evoField.h"

class SimpleNetwork
{
    float *foodNeurons;
    float *wallNeurons;

    public:
        SimpleNetwork();
        ~SimpleNetwork();
        
        int useMind(EvoField &evoField, int headX, int headY);
        void mergeNetworks(SimpleNetwork *parentOne, SimpleNetwork *parentTwo);
        

    private:
        int neuronActivity(float result);
        float validateResult(float result, float weight);

};

#endif