#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "Screen/screen.h"
#include "Evolution/Bars/evoInfoBar.h"
#include "Evolution/Bars/evoToolsBar.h"
#include "Evolution/Bars/evoSquareBar.h"
#include "Evolution/Models/snakeEvoModel.h"
#include "Evolution/Parameters/evolutionParameters.h"

extern Screen currentScreen;
extern EvolutionParameters evolutionParameters;

class Evolution
{
    public:
        Evolution()
            : infoBar(evolutionParameters.infoBarStartX, evolutionParameters.infoBarStartY, evolutionParameters.infoBarEndX, evolutionParameters.infoBarEndY),
            toolsBar(evolutionParameters.toolsBarStartX, evolutionParameters.toolsBarStartY, evolutionParameters.toolsBarEndX, evolutionParameters.toolsBarEndY),
            squareBar(evolutionParameters.squareBarStartX, evolutionParameters.squareBarStartY, evolutionParameters.squareBarEndX, evolutionParameters.squareBarEndY) {};
        ~Evolution() {};
	    void run();


    private:
        EvoInfoBar infoBar;
        EvoToolsBar toolsBar;
        EvoSquareBar squareBar;

        int key = 0;

        SnakeEvoModel *snakes = nullptr;

        struct snakesRatingList{
            int snakeNumber;
            int snakeScore;
            struct snakesRatingList *nextPlace;
            struct snakesRatingList *prevPlace;
        };

        void turn(SnakeEvoModel *snakes);
        void drawScreen();
        void evolveSnakes();
        snakesRatingList* getParentsList(SnakeEvoModel *snakes);
        void initSnakes(SnakeEvoModel *snakes);
        void drawStuff();
        void deleteSnakes(SnakeEvoModel *snakes);
/*
        //Save-load
        int saveGame(snakesList *thisSnakes) {};
        int loadGame(snakesList *thisSnakes) {};
        static int saveSnakes(void *NotUsed, int argc, char **argv, char **azColName) {};
        static int loadSession(void *NotUsed, int argc, char **argv, char **azColName) {};
        static int loadSnake(void *NotUsed, int argc, char **argv, char **azColName) {};
        static int loadNeurons(void *NotUsed, int argc, char **argv, char **azColName) {};*/

};
#endif
