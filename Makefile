CC=g++
SYSTEMTYPE=-D LINUX
CFLAGS=-c -Wall
LIBFLAGS=-lncurses

ROOT=src/
MAIN=$(ROOT)Main/
SCREEN=$(ROOT)Screen/
MENUS=$(ROOT)Menus/
MODES=$(ROOT)Modes/

SNAKEGAME=$(MODES)SnakeGame/
SNAKEGAME_MODELS=$(SNAKEGAME)Models/
SNAKEGAME_MENUS=$(SNAKEGAME)Menus/

EVOLUTION=$(MODES)Evolution/
EVOLUTION_FIELD=$(EVOLUTION)Field/
EVOLUTION_MODELS=$(EVOLUTION)Models/
EVOLUTION_MENUS=$(EVOLUTION)Menus/
EVOLUTION_SUBMENUS=$(EVOLUTION_MENUS)SubMenus/

LIFEGAME=$(MODES)LifeGame/
LIFEGAME_FIELD=$(LIFEGAME)Field/
LIFEGAME_MENUS=$(LIFEGAME)Menus/
LIFEGAME_SUBMENUS=$(LIFEGAME_MENUS)SubMenus/

all: main

main: 
	$(CC) $(SYSTEMTYPE) \
	$(MAIN)main.cpp \
	$(SCREEN)screen.cpp \
	$(MENUS)menu.cpp \
	$(MENUS)mainmenu.cpp \
	$(MENUS)modeSelector.cpp \
	$(MENUS)settingsMenu.cpp \
	$(MENUS)controllsMenu.cpp \
	$(SNAKEGAME)snakeGame.cpp \
	$(SNAKEGAME_MODELS)snakeModel.cpp \
	$(SNAKEGAME_MODELS)foodModel.cpp \
	$(SNAKEGAME_MENUS)pauseMenu.cpp \
	$(SNAKEGAME_MENUS)snakeSettingsMenu.cpp \
	$(EVOLUTION)evolution.cpp \
	$(EVOLUTION_FIELD)map.cpp \
	$(EVOLUTION_MODELS)snakeEvolutionModel.cpp \
	$(EVOLUTION_MODELS)foodEvolutionModel.cpp \
	$(EVOLUTION_SUBMENUS)infoSubMenu.cpp \
	$(EVOLUTION_SUBMENUS)toolsSubMenu.cpp \
	$(LIFEGAME)lifeGame.cpp \
	$(LIFEGAME_FIELD)lifeMap.cpp \
	$(LIFEGAME_SUBMENUS)lifeInfoSubMenu.cpp \
	$(LIFEGAME_SUBMENUS)lifeToolsSubMenu.cpp \
	$(LIBFLAGS) -o snake

clean:
	rm -rf *.o
