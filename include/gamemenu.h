#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <SDL2/SDL.h>
#include <stdbool.h>
struct GameMenuAssets {
        SDL_Texture* continue_white;
        SDL_Texture* continue_green;
        SDL_Rect continue_pos;
        bool is_continue_selected;

        SDL_Texture* menu_white;
        SDL_Texture* menu_green;
        SDL_Rect menu_pos;
        bool is_menu_selected;

        bool game_over;
};
int handleGameMenuEvents(SDL_Event*);
void setupGameMenu();
void drawGameMenu(int);
void updateGameMenu();
void cleanupGameMenu();
#endif
