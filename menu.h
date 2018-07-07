#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
int handleMenuEvents(SDL_Event* e);
void setupMenu();
void drawMenu();
void updateMenuScreen();
void cleanupMenuScreen();
#endif
