#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "gamemenu.h"
#include "display.h"
#include "menu.h"
extern TTF_Font* font;
extern const int SCREEN_W;
extern const int SCREEN_H;

struct GameMenuAssets game_menu;
/*
Return 0 for main_menu
Return 1 for Continue
Return 2 for Upgrades
Return -1 for nothing
*/
int mousePressGame(SDL_MouseButtonEvent b) {
        if(b.button == SDL_BUTTON_LEFT) {
                //Main Menu Button
                if(checkBoundaries(b.x, b.y, game_menu.menu_pos)) {
                        return 0;
                }

                //Continue Button
                if(checkBoundaries(b.x, b.y, game_menu.continue_pos)
                                && !game_menu.game_over) {
                        return 1;
                }

                //Upgrades Button
                if(checkBoundaries(b.x, b.y, game_menu.upgrades_pos)) {
                        return 2;
                }
                else return -1;
        }
        else return -1;
}

void mouseSelectGame() {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        if(checkBoundaries(mouse_x, mouse_y, game_menu.continue_pos)) {
                game_menu.is_continue_selected = true;
        }
        else {
                game_menu.is_continue_selected = false;
        }

        if(checkBoundaries(mouse_x, mouse_y, game_menu.menu_pos)) {
                game_menu.is_menu_selected = true;
        }
        else {
                game_menu.is_menu_selected = false;
        }

        if(checkBoundaries(mouse_x, mouse_y, game_menu.upgrades_pos)) {
                game_menu.is_upgrades_selected = true;
        }
        else {
                game_menu.is_upgrades_selected = false;
        }
}
/*
Return 0 for main_menu
Return 1 for Continue
Retrun 2 for Upgrades
Return -1 for nothing
*/
int handleGameMenuEvents(SDL_Event* e) {
        int button = -1;
        while(SDL_PollEvent(e)) {
                mouseSelectGame();
                if(e -> type == SDL_QUIT) {
                       button = 0;
                }
                else if(e -> type == SDL_MOUSEBUTTONDOWN) {
                       button = mousePressGame(e -> button);
                       return button;
                }
        }
        return -1;
}
void setupGameMenu() {
        SDL_Color white = {255, 255, 255};
        SDL_Color green = {144, 245, 0};
        SDL_Color red = {255, 17, 0};
        game_menu.menu_white = createTextTexture(font, "Main Menu", white);
        game_menu.menu_green = createTextTexture(font, "Main Menu", green);
        game_menu.menu_pos.w = 800;
        game_menu.menu_pos.h = 100;
        game_menu.menu_pos.x = (SCREEN_W / 2) - game_menu.menu_pos.w / 2;
        game_menu.menu_pos.y = (SCREEN_H / 2) + 20;

        game_menu.continue_white = createTextTexture(font, "Continue", white);
        game_menu.continue_green = createTextTexture(font, "Continue", green);
        game_menu.continue_red = createTextTexture(font, "Continue", red);
        game_menu.continue_pos.w = 800;
        game_menu.continue_pos.h = 100;
        game_menu.continue_pos.x = (SCREEN_W / 2) - game_menu.continue_pos.w / 2;
        game_menu.continue_pos.y = (SCREEN_H / 2) - 200;

        game_menu.upgrades_white = createTextTexture(font, "Upgrades", white);
        game_menu.upgrades_green = createTextTexture(font, "Upgrades", green);
        game_menu.upgrades_pos.w = 800;
        game_menu.upgrades_pos.h = 100;
        game_menu.upgrades_pos.x = (SCREEN_W / 2) - game_menu.upgrades_pos.w / 2;
        game_menu.upgrades_pos.y = (SCREEN_H / 2) - 100;
        game_menu.game_over = false;
}

void updateGameMenu(int game_outcome) {
        if(game_outcome == 1) {
                game_menu.game_over = true;
        }
        renderPresent();
        SDL_Color black = {0, 0, 0};
        setDrawColor(black);
        clearRender();
}

void drawGameMenu() {
        if(game_menu.is_menu_selected) {
                renderTexture(game_menu.menu_green, NULL, &game_menu.menu_pos);
        }
        else {
                renderTexture(game_menu.menu_white, NULL, &game_menu.menu_pos);
        }

        if(game_menu.is_continue_selected) {
                if(game_menu.game_over) {
                        renderTexture(game_menu.continue_red, NULL, &game_menu.continue_pos);
                }
                else {
                        renderTexture(game_menu.continue_green, NULL, &game_menu.continue_pos);
                }
        }
        else {
                renderTexture(game_menu.continue_white, NULL, &game_menu.continue_pos);
        }

        if(game_menu.is_upgrades_selected) {
                renderTexture(game_menu.upgrades_green, NULL, &game_menu.upgrades_pos);
        }
        else {
                renderTexture(game_menu.upgrades_white, NULL, &game_menu.upgrades_pos);
        }
}

void cleanupGameMenu() {
        SDL_DestroyTexture(game_menu.continue_white);
        SDL_DestroyTexture(game_menu.continue_green);
        SDL_DestroyTexture(game_menu.continue_red);
        SDL_DestroyTexture(game_menu.menu_white);
        SDL_DestroyTexture(game_menu.menu_green);
        SDL_DestroyTexture(game_menu.upgrades_white);
        SDL_DestroyTexture(game_menu.upgrades_green);
}
