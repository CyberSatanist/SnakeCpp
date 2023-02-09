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
        "Count of Neural Layers",
        "Count of Neurons in Layer"
    };

    buttonChoices = { "Back" };
    
    rows = (int) menuChoices.size() / 2;
    columns = (int) menuChoices.size() / rows;
    colorsFrom = 5;
    firstMenuTitle = GameSpeed;
    lastMenuTitle = NeuronsCount;
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
            case LayersCount:
                if (evolutionParameters.countOfLayers == 1){
                    evolutionParameters.countOfLayers = 20;
                } else {
                    evolutionParameters.countOfLayers--;
                }
                break;
            case NeuronsCount:
                if (evolutionParameters.countOfNeuronsInLayer == 1){
                    evolutionParameters.countOfNeuronsInLayer = 100;
                } else {
                    evolutionParameters.countOfNeuronsInLayer--;
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
            case LayersCount:
                if (evolutionParameters.countOfLayers == 20){
                    evolutionParameters.countOfLayers = 1;
                } else {
                    evolutionParameters.countOfLayers++;
                }
                break;
            case NeuronsCount:
                if (evolutionParameters.countOfNeuronsInLayer == 100){
                    evolutionParameters.countOfNeuronsInLayer = 1;
                } else {
                    evolutionParameters.countOfNeuronsInLayer++;
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
        case LayersCount:
            return evolutionParameters.countOfLayers;
            break;
        case NeuronsCount:
            return evolutionParameters.countOfNeuronsInLayer;
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