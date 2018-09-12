#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "menu.h"
struct GameMenuAssets {
        SDL_Texture* continue_white;
        SDL_Texture* continue_green;
        SDL_Texture* continue_red;
        SDL_Rect continue_pos;
        bool is_continue_selected;
        struct Button cont;

        SDL_Texture* menu_white;
        SDL_Texture* menu_green;
        SDL_Rect menu_pos;
        bool is_menu_selected;
        struct Button menu;

        SDL_Texture* upgrades_white;
        SDL_Texture* upgrades_green;
        SDL_Rect upgrades_pos;
        bool is_upgrades_selected;
        struct Button upgrades;
        
        bool game_over;
};
int handleGameMenuEvents(SDL_Event*);
void setupGameMenu();
void drawGameMenu();
void updateGameMenu(int);
void cleanupGameMenu();
#endif
