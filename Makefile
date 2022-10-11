CC=g++
SYSTEMTYPE=-D LINUX
CFLAGS=-c
WARNINGS=-Wall
DEBUG=-g -O0
LOGS=-D LOGS
LIBFLAGS=-lncurses
SOURCES=-I src/ -I src/Modes/

ROOT=src/
MAIN=$(ROOT)Main/
SCREEN=$(ROOT)Screen/
FIELD=$(ROOT)Field/
MENUS=$(ROOT)Menus/
BARS=$(ROOT)Bars/
MODES=$(ROOT)Modes/

SNAKEGAME=$(MODES)SnakeGame/
SNAKEGAME_MODELS=$(SNAKEGAME)Models/
SNAKEGAME_MENUS=$(SNAKEGAME)Menus/

EVOLUTION=$(MODES)Evolution/
EVOLUTION_FIELD=$(EVOLUTION)Field/
EVOLUTION_MODELS=$(EVOLUTION)Models/
EVOLUTION_MENUS=$(EVOLUTION)Menus/
EVOLUTION_NEURAL_NETWORK=$(EVOLUTION)NeuralNetwork/
EVOLUTION_BARS=$(EVOLUTION)Bars/

LIFEGAME=$(MODES)LifeGame/
LIFEGAME_FIELD=$(LIFEGAME)Field/
LIFEGAME_MENUS=$(LIFEGAME)Menus/
LIFEGAME_BARS=$(LIFEGAME)Bars/

all: main

main: 
	$(CC) $(SYSTEMTYPE) $(SOURCES) \
	$(MAIN)main.cpp \
	$(SCREEN)screen.cpp \
	$(FIELD)field.cpp \
	$(BARS)infoBar.cpp \
	$(BARS)toolsBar.cpp \
	$(BARS)squareBar.cpp \
	$(MENUS)menu.cpp \
	$(MENUS)mainmenu.cpp \
	$(MENUS)modeSelector.cpp \
	$(MENUS)settings.cpp \
	$(MENUS)settingsMenu.cpp \
	$(MENUS)controllsMenu.cpp \
	$(SNAKEGAME)snakeGame.cpp \
	$(SNAKEGAME_MODELS)snakeModel.cpp \
	$(SNAKEGAME_MODELS)foodModel.cpp \
	$(SNAKEGAME_MENUS)pauseMenu.cpp \
	$(SNAKEGAME_MENUS)snakeSettingsMenu.cpp \
	$(EVOLUTION)evolution.cpp \
	$(EVOLUTION_FIELD)evoField.cpp \
	$(EVOLUTION_MODELS)snakeEvoModel.cpp \
	$(EVOLUTION_MENUS)evoSettingsMenu.cpp \
	$(EVOLUTION_NEURAL_NETWORK)standartNetwork.cpp \
	$(EVOLUTION_NEURAL_NETWORK)standartNeuron.cpp \
	$(EVOLUTION_BARS)evoInfoBar.cpp \
	$(EVOLUTION_BARS)evoToolsBar.cpp \
	$(EVOLUTION_BARS)evoSquareBar.cpp \
	$(LIFEGAME)lifeGame.cpp \
	$(LIFEGAME_FIELD)lifeField.cpp \
	$(LIFEGAME_BARS)lifeInfoBar.cpp \
	$(LIFEGAME_BARS)lifeToolsBar.cpp \
	$(LIBFLAGS) -o snake


debug:
	$(CC) $(SYSTEMTYPE) $(SOURCES) $(DEBUG) $(WARNINGS) \
	$(MAIN)main.cpp \
	$(SCREEN)screen.cpp \
	$(FIELD)field.cpp \
	$(BARS)infoBar.cpp \
	$(BARS)toolsBar.cpp \
	$(BARS)squareBar.cpp \
	$(MENUS)menu.cpp \
	$(MENUS)mainmenu.cpp \
	$(MENUS)modeSelector.cpp \
	$(MENUS)settings.cpp \
	$(MENUS)settingsMenu.cpp \
	$(MENUS)controllsMenu.cpp \
	$(SNAKEGAME)snakeGame.cpp \
	$(SNAKEGAME_MODELS)snakeModel.cpp \
	$(SNAKEGAME_MODELS)foodModel.cpp \
	$(SNAKEGAME_MENUS)pauseMenu.cpp \
	$(SNAKEGAME_MENUS)snakeSettingsMenu.cpp \
	$(EVOLUTION)evolution.cpp \
	$(EVOLUTION_FIELD)evoField.cpp \
	$(EVOLUTION_MODELS)snakeEvoModel.cpp \
	$(EVOLUTION_MENUS)evoSettingsMenu.cpp \
	$(EVOLUTION_NEURAL_NETWORK)standartNetwork.cpp \
	$(EVOLUTION_NEURAL_NETWORK)standartNeuron.cpp \
	$(EVOLUTION_BARS)evoInfoBar.cpp \
	$(EVOLUTION_BARS)evoToolsBar.cpp \
	$(EVOLUTION_BARS)evoSquareBar.cpp \
	$(LIFEGAME)lifeGame.cpp \
	$(LIFEGAME_FIELD)lifeField.cpp \
	$(LIFEGAME_BARS)lifeInfoBar.cpp \
	$(LIFEGAME_BARS)lifeToolsBar.cpp \
	$(LIBFLAGS) -o snakeDebug

datalogs:
	$(CC) $(SYSTEMTYPE) $(SOURCES) $(LOGS) $(WARNINGS) \
	$(MAIN)main.cpp \
	$(SCREEN)screen.cpp \
	$(FIELD)field.cpp \
	$(BARS)infoBar.cpp \
	$(BARS)toolsBar.cpp \
	$(BARS)squareBar.cpp \
	$(MENUS)menu.cpp \
	$(MENUS)mainmenu.cpp \
	$(MENUS)modeSelector.cpp \
	$(MENUS)settings.cpp \
	$(MENUS)settingsMenu.cpp \
	$(MENUS)controllsMenu.cpp \
	$(SNAKEGAME)snakeGame.cpp \
	$(SNAKEGAME_MODELS)snakeModel.cpp \
	$(SNAKEGAME_MODELS)foodModel.cpp \
	$(SNAKEGAME_MENUS)pauseMenu.cpp \
	$(SNAKEGAME_MENUS)snakeSettingsMenu.cpp \
	$(EVOLUTION)evolution.cpp \
	$(EVOLUTION_FIELD)evoField.cpp \
	$(EVOLUTION_MODELS)snakeEvoModel.cpp \
	$(EVOLUTION_MENUS)evoSettingsMenu.cpp \
	$(EVOLUTION_NEURAL_NETWORK)standartNetwork.cpp \
	$(EVOLUTION_NEURAL_NETWORK)standartNeuron.cpp \
	$(EVOLUTION_BARS)evoInfoBar.cpp \
	$(EVOLUTION_BARS)evoToolsBar.cpp \
	$(EVOLUTION_BARS)evoSquareBar.cpp \
	$(LIFEGAME)lifeGame.cpp \
	$(LIFEGAME_FIELD)lifeField.cpp \
	$(LIFEGAME_BARS)lifeInfoBar.cpp \
	$(LIFEGAME_BARS)lifeToolsBar.cpp \
	$(LIBFLAGS) -o snakeLogs

debugAndLogs:
	$(CC) $(SYSTEMTYPE) $(SOURCES) $(DEBUG) $(LOGS) $(WARNINGS) \
	$(MAIN)main.cpp \
	$(SCREEN)screen.cpp \
	$(FIELD)field.cpp \
	$(BARS)infoBar.cpp \
	$(BARS)toolsBar.cpp \
	$(BARS)squareBar.cpp \
	$(MENUS)menu.cpp \
	$(MENUS)mainmenu.cpp \
	$(MENUS)modeSelector.cpp \
	$(MENUS)settings.cpp \
	$(MENUS)settingsMenu.cpp \
	$(MENUS)controllsMenu.cpp \
	$(SNAKEGAME)snakeGame.cpp \
	$(SNAKEGAME_MODELS)snakeModel.cpp \
	$(SNAKEGAME_MODELS)foodModel.cpp \
	$(SNAKEGAME_MENUS)pauseMenu.cpp \
	$(SNAKEGAME_MENUS)snakeSettingsMenu.cpp \
	$(EVOLUTION)evolution.cpp \
	$(EVOLUTION_FIELD)evoField.cpp \
	$(EVOLUTION_MODELS)snakeEvoModel.cpp \
	$(EVOLUTION_MENUS)evoSettingsMenu.cpp \
	$(EVOLUTION_NEURAL_NETWORK)standartNetwork.cpp \
	$(EVOLUTION_NEURAL_NETWORK)standartNeuron.cpp \
	$(EVOLUTION_BARS)evoInfoBar.cpp \
	$(EVOLUTION_BARS)evoToolsBar.cpp \
	$(EVOLUTION_BARS)evoSquareBar.cpp \
	$(LIFEGAME)lifeGame.cpp \
	$(LIFEGAME_FIELD)lifeField.cpp \
	$(LIFEGAME_BARS)lifeInfoBar.cpp \
	$(LIFEGAME_BARS)lifeToolsBar.cpp \
	$(LIBFLAGS) -o snakeDebugAndLogs




clean:
	rm -rf *.o
