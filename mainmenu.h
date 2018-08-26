#ifndef MAINMENU_H
#define MAINMENU_H
#include <SDL2/SDL.h>
#include <stdbool.h>
struct MainMenuAssets {
        SDL_Texture* start_white;
        SDL_Texture* start_green;
        SDL_Rect start_pos;
        bool is_start_selected;

        SDL_Texture* quit_white;
        SDL_Texture* quit_green;
        SDL_Rect quit_pos;
        bool is_quit_selected;

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
