CC=g++
SYSTEMTYPE=-D LINUX
CFLAGS=-c -Wall
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
	$(EVOLUTION_MODELS)foodEvoModel.cpp \
	$(EVOLUTION_BARS)evoInfoBar.cpp \
	$(EVOLUTION_BARS)evoToolsBar.cpp \
	$(EVOLUTION_BARS)evoSquareBar.cpp \
	$(LIFEGAME)lifeGame.cpp \
	$(LIFEGAME_FIELD)lifeField.cpp \
	$(LIFEGAME_BARS)lifeInfoBar.cpp \
	$(LIFEGAME_BARS)lifeToolsBar.cpp \
	$(LIBFLAGS) -o snake

clean:
	rm -rf *.o
