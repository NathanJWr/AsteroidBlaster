#ifndef MAINMENU_H
#define MAINMENU_H
#include <SDL2/SDL.h>
int handleMainMenuEvents(SDL_Event* e);
void setupMainMenu();
void drawMainMenu();
void updateMainMenu();
void cleanupMainMenu();
#endif
