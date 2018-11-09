#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "menu.h"
struct GameMenuAssets {
  Button cont;
  Button upgrades;
  Button menu;
  
  bool game_over;
};
int handleGameMenuEvents(SDL_Event*);
void setupGameMenu();
void drawGameMenu();
void updateGameMenu(int);
void cleanupGameMenu();
#endif
