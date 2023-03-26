#include "evoSettingsMenu.h"
#include "Evolution/Parameters/evolutionParameters.h"

extern EvolutionParameters evolutionParameters;


EvoSettingsMenu::EvoSettingsMenu()
{
    menuTitle = "   ~E V O  S E T T I N G S  M E N U~   ";

    menuChoices = {
        "Game speed",
        "Length of snakes",
        "Count of snakes",
        "Count of foods",
        "Count of Neurons in Input Layer",
        "Count of Hidden Layers",
        "Count of Neurons in Hidden Layer",
        "Count of Neurons in Output Layer",
    };

    buttonChoices = { "Back" };
    
    rows = (int) menuChoices.size() / 2;
    columns = (int) menuChoices.size() / rows;
    colorsFrom = 5;
    firstMenuTitle = GameSpeed;
    lastMenuTitle = OutputLayerNeuronsCount;
};


void EvoSettingsMenu::setParameter(int currentChoice, int side)
{
    if (side == Screen::controll_keys::LEFT){
        switch (currentChoice) {
            case GameSpeed:
                if (evolutionParameters.delayDuration == 1){
                    evolutionParameters.delayDuration = 200;
                } else {
                    evolutionParameters.delayDuration -= 1;
                }
                break;
            case SnakesLength:
                if (evolutionParameters.snakeLength == 1){
                    evolutionParameters.snakeLength = 30;
                } else {
                    evolutionParameters.snakeLength--;
                }
                break;
            case SnakesCount:
                if (evolutionParameters.countOfSnakes == 1){
                    evolutionParameters.countOfSnakes = 1000;
                } else {
                    evolutionParameters.countOfSnakes--;
                }
                break;
            case FoodsCount:
                if (evolutionParameters.countOfFood == 1){
                    evolutionParameters.countOfFood = 500;
                } else {
                    evolutionParameters.countOfFood--;
                }
                break;
            case InputLayerNeuronsCount:
                if (evolutionParameters.inputLayerNeuronCount == 1){
                    evolutionParameters.inputLayerNeuronCount = 121;
                } else {
                    evolutionParameters.inputLayerNeuronCount--;
                }
                break;
            case HiddenLayersCount:
                if (evolutionParameters.countOfHiddenLayers == 1){
                    evolutionParameters.countOfHiddenLayers = 30;
                } else {
                    evolutionParameters.countOfHiddenLayers--;
                }
                break;
            case HiddenLayerNeuronsCount:
                if (evolutionParameters.hiddenLayerNeuronCount == 1){
                    evolutionParameters.hiddenLayerNeuronCount = 121;
                } else {
                    evolutionParameters.hiddenLayerNeuronCount--;
                }
                break;
            case OutputLayerNeuronsCount:
                if (evolutionParameters.outputLayerNeuronCount == 1){
                    evolutionParameters.outputLayerNeuronCount = 121;
                } else {
                    evolutionParameters.outputLayerNeuronCount--;
                }
                break;
        }
    } else if (side == Screen::controll_keys::RIGHT){
        switch (currentChoice) {
            case GameSpeed:
                if (evolutionParameters.delayDuration == 200){
                    evolutionParameters.delayDuration = 1;
                } else {
                    evolutionParameters.delayDuration += 1;
                }
                break;
            case SnakesLength:
                if (evolutionParameters.snakeLength == 30){
                    evolutionParameters.snakeLength = 1;
                } else {
                    evolutionParameters.snakeLength++;
                }
                break;
            case SnakesCount:
                if (evolutionParameters.countOfSnakes == 1000){
                    evolutionParameters.countOfSnakes = 1;
                } else {
                    evolutionParameters.countOfSnakes++;
                }
                break;
            case FoodsCount:
                if (evolutionParameters.countOfFood == 500){
                    evolutionParameters.countOfFood = 1;
                } else {
                    evolutionParameters.countOfFood++;
                }
                break;
            case InputLayerNeuronsCount:
                if (evolutionParameters.inputLayerNeuronCount == 121){
                    evolutionParameters.inputLayerNeuronCount = 1;
                } else {
                    evolutionParameters.inputLayerNeuronCount++;
                }
                break;
            case HiddenLayersCount:
                if (evolutionParameters.countOfHiddenLayers == 30){
                    evolutionParameters.countOfHiddenLayers = 1;
                } else {
                    evolutionParameters.countOfHiddenLayers++;
                }
                break;
            case HiddenLayerNeuronsCount:
                if (evolutionParameters.hiddenLayerNeuronCount == 121){
                    evolutionParameters.hiddenLayerNeuronCount = 1;
                } else {
                    evolutionParameters.hiddenLayerNeuronCount++;
                }
                break;
            case OutputLayerNeuronsCount:
                if (evolutionParameters.outputLayerNeuronCount == 121){
                    evolutionParameters.outputLayerNeuronCount = 1;
                } else {
                    evolutionParameters.outputLayerNeuronCount++;
                }
                break;
        }
    }
}


int EvoSettingsMenu::getParameter(int count)
{
    switch(count) {
        case GameSpeed:
            return evolutionParameters.delayDuration;
            break;
        case SnakesLength:
            return evolutionParameters.snakeLength;
            break;
        case SnakesCount:
            return evolutionParameters.countOfSnakes;
            break;
        case FoodsCount:
            return evolutionParameters.countOfFood;
            break;
        case InputLayerNeuronsCount:
            return evolutionParameters.inputLayerNeuronCount;
            break;
        case HiddenLayersCount:
            return evolutionParameters.countOfHiddenLayers;
            break;
        case HiddenLayerNeuronsCount:
            return evolutionParameters.hiddenLayerNeuronCount;
            break;
        case OutputLayerNeuronsCount:
            return evolutionParameters.outputLayerNeuronCount;
            break;
        default:
            return 0;
    }
}


void EvoSettingsMenu::menuControllSelect()
{
    if (currentChoice == ((int) menuChoices.size() + (int) buttonChoices.size() - 1)){
        settingsOn = false;
    }
}