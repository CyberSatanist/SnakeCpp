#ifndef STANDART_NEURON_H
#define STANDART_NEURON_H

class StandartNeuron
{
    public:
        float input;
        int neuronId;
        StandartNeuron();

        struct Connections {
            float synapse;
            StandartNeuron *currentNeuron;
            struct Connections *nextConnection;
        };
        Connections* firstConnection = new Connections;
        Connections* tmpConnection = new Connections;
        Connections* tmpSecondConnection = new Connections;

    private:

};

#endif