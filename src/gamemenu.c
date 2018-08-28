#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "gamemenu.h"
#include "display.h"
extern TTF_Font* font;
extern SDL_Renderer* renderer;
extern const int SCREEN_W;
extern const int SCREEN_H;

struct GameMenuAssets game_menu;

/*
Return 0 for main_menu
Return 1 for Continue
Return -1 for nothing
*/
int mousePressGame(SDL_MouseButtonEvent b) {
        if(b.button == SDL_BUTTON_LEFT) {
                //Continue Button
                if(b.x >= game_menu.continue_pos.x
                                && b.x <= game_menu.continue_pos.x 
                                        + game_menu.continue_pos.w
                                && b.y >= game_menu.continue_pos.y
                                && b.y <= game_menu.continue_pos.y 
                                        + game_menu.continue_pos.h) {
                        return 1;
                }

                //Main Menu Button
                if(b.x >= game_menu.menu_pos.x
                                && b.x <= game_menu.menu_pos.x 
                                        + game_menu.menu_pos.w
                                && b.y >= game_menu.menu_pos.y
                                && b.y <= game_menu.menu_pos.y 
                                        + game_menu.menu_pos.h) {
                        return 0;
                }
                else return -1;
        }
        else return -1;
}

void mouseSelectGame() {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(mouse_x >= game_menu.continue_pos.x
                        && mouse_x <= game_menu.continue_pos.x 
                                + game_menu.continue_pos.w
                        && mouse_y >= game_menu.continue_pos.y
                        && mouse_y <= game_menu.continue_pos.y 
                                + game_menu.continue_pos.h) {

                game_menu.is_continue_selected = true;
        }
        else {
                game_menu.is_continue_selected = false;
        }
        if(mouse_x >= game_menu.menu_pos.x
                        && mouse_x <= game_menu.menu_pos.x 
                                + game_menu.menu_pos.w
                        && mouse_y >= game_menu.menu_pos.y
                        && mouse_y <= game_menu.menu_pos.y 
                                + game_menu.menu_pos.h) {

                game_menu.is_menu_selected = true;
        }
        else {
                game_menu.is_menu_selected = false;
        }
}
/*
Return 0 for main_menu
Return 1 for Continue
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
        game_menu.menu_white = IMG_LoadTexture(renderer,
                        "assets/mainmenu_text.png");
        game_menu.menu_green = IMG_LoadTexture(renderer,
                        "assets/mainmenu_text_green.png");
        game_menu.menu_pos.w = 800;
        game_menu.menu_pos.h = 100;
        game_menu.menu_pos.x = (SCREEN_W / 2) - game_menu.menu_pos.w / 2;
        game_menu.menu_pos.y = (SCREEN_H / 2) + 20;

        game_menu.continue_white = IMG_LoadTexture(renderer, 
                        "assets/continue_text.png");
        game_menu.continue_green = IMG_LoadTexture(renderer,
                        "assets/continue_text_green.png");
        game_menu.continue_pos.w = 800;
        game_menu.continue_pos.h = 100;
        game_menu.continue_pos.x = (SCREEN_W / 2) - game_menu.continue_pos.w / 2;
        game_menu.continue_pos.y = (SCREEN_H / 2) - 100;
}

void updateGameMenu() {
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
}

void drawGameMenu(int game_outcome) {
        if(game_outcome == 0) {
                if(game_menu.is_menu_selected) {
                        SDL_RenderCopy(renderer, game_menu.menu_green,
                                        NULL, &game_menu.menu_pos);
                }
                else {
                        SDL_RenderCopy(renderer, game_menu.menu_white,
                                        NULL, &game_menu.menu_pos);
                }

                if(game_menu.is_continue_selected) {
                        SDL_RenderCopy(renderer, game_menu.continue_green,
                                        NULL, &game_menu.continue_pos);
                }
                else {
                        SDL_RenderCopy(renderer, game_menu.continue_white,
                                        NULL, &game_menu.continue_pos);
                }
        }
        if(game_outcome == 1) {
                SDL_RenderCopy(renderer, game_menu.menu_white, NULL,
                                &game_menu.menu_pos);
        }
}

void cleanupGameMenu() {
        SDL_DestroyTexture(game_menu.continue_white);
        SDL_DestroyTexture(game_menu.continue_green);
        SDL_DestroyTexture(game_menu.menu_white);
        SDL_DestroyTexture(game_menu.menu_green);
}
