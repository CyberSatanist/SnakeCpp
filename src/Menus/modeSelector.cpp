#include "modeSelector.h"
#include "SnakeGame/snakeGame.h"
#include "Evolution/evolution.h"
#include "LifeGame/lifeGame.h"


ModeSelector::ModeSelector()
{
    menuTitle = "   ~M O D E  S E L E C T O R~   ";

    menuChoices = 
    {
        "Snake Game",
        "Evolution",
        "Life Game",
        "Back"
    };
}


void ModeSelector::menuControllSelect()
{
    if (currentChoice == menuChoicesConst::SnakeGameChoice){
        SnakeGame *snakeGame = new SnakeGame;
	    snakeGame->run();
        delete snakeGame;
    } else if (currentChoice == menuChoicesConst::EvolutionChoice){
        Evolution *evolution = new Evolution;
	    evolution->run();
        delete evolution;
    } else if (currentChoice == menuChoicesConst::LifeGameChoice){
        LifeGame *lifeGame = new LifeGame;
	    lifeGame->run();
        delete lifeGame;
    } else if (currentChoice == menuChoicesConst::Back){
        menuOn = false;
    }
}
