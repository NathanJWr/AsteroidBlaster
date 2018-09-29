#ifndef MAINMENU_H
#define MAINMENU_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "menu.h"
struct MainMenuAssets {
        Button start;
        Button quit;

        SDL_Texture* background1;
        SDL_Texture* background2;
        SDL_Rect background1_pos;
        SDL_Rect background2_pos;
        int background_offset;

        SDL_Texture* logo;
        SDL_Rect logo_pos;
};
int handleMainMenuEvents(SDL_Event* e);
void setupMainMenu();
void drawMainMenu();
void updateMainMenu();
void cleanupMainMenu();
#endif
