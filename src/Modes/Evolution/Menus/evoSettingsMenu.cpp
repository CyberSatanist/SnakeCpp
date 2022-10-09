#include "evoSettingsMenu.h"
#include <Evolution/Parameters/evolutionParameters.h>

extern EvolutionParameters evolutionParameters;


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
                    evolutionParameters.countOfSnakes = 100;
                } else {
                    evolutionParameters.countOfSnakes--;
                }
                break;
            case FoodsCount:
                if (evolutionParameters.countOfFood == 1){
                    evolutionParameters.countOfFood = 100;
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
                    evolutionParameters.countOfNeuronsInLayer = 20;
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
                if (evolutionParameters.countOfSnakes == 100){
                    evolutionParameters.countOfSnakes = 1;
                } else {
                    evolutionParameters.countOfSnakes++;
                }
                break;
            case FoodsCount:
                if (evolutionParameters.countOfFood == 100){
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
                if (evolutionParameters.countOfNeuronsInLayer == 20){
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
    if (currentChoice == (menuConst + buttonsConst - 1)){
        settingsOn = false;
    }
}


void EvoSettingsMenu::writeString(int count)
{
    const char *string = menuChoices[count].c_str();
    currentScreen.writeText(string);
}


void EvoSettingsMenu::writeButton(int count)
{
    const char *string = buttonChoices[count].c_str();
    currentScreen.writeText(string);
}