#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "menu.h"
struct GameMenuAssets {
        struct Button cont;
        struct Button upgrades;
        struct Button menu;
        
        bool game_over;
};
int handleGameMenuEvents(SDL_Event*);
void setupGameMenu();
void drawGameMenu();
void updateGameMenu(int);
void cleanupGameMenu();
#endif
