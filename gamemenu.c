#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "gamemenu.h"
#include "display.h"
extern TTF_Font* font;
extern SDL_Renderer* renderer;
extern const int SCREEN_W;
extern const int SCREEN_H;

SDL_Texture* menu_texture;
SDL_Texture* continue_texture;
SDL_Rect menu_pos;
SDL_Rect continue_pos;

int menu_w;
int menu_h;
int continue_w;
int continue_h;
int mousePressGame(SDL_MouseButtonEvent b) {
        if(b.button == SDL_BUTTON_LEFT) {
                //Continue Button
                if(b.x >= continue_pos.x
                                && b.x <= continue_pos.x + continue_w
                                && b.y >= continue_pos.y
                                && b.y <= continue_pos.y + continue_h) {
                        return 1;
                }
                //Main Menu Button
                else if(b.x >= menu_pos.x
                                && b.x <= menu_pos.x + menu_w
                                && b.y >= menu_pos.y
                                && b.y <= menu_pos.y + menu_h) {
                        return 0;
                }
                else return -1;
        }
        else return -1;
}
/*
Return 0 for main_menu
Return 1 for Continue
*/
int handleGameMenuEvents(SDL_Event* e) {
        int button = -1;
        while(SDL_PollEvent(e)) {
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
        SDL_Color text_color = {255, 255, 255, 255};
        SDL_Surface* main_menu = TTF_RenderText_Solid(font, "Main Menu", text_color);
        SDL_Surface* cont = TTF_RenderText_Solid(font, "Continue", text_color);

        menu_w = main_menu -> w;
        menu_h = main_menu -> h;
        continue_w = cont -> w;
        continue_h = cont -> h;

        continue_pos.x = (SCREEN_W / 2) - continue_w / 2;
        continue_pos.y = (SCREEN_H / 2) - 100;
        menu_pos.x = (SCREEN_W / 2) - menu_w / 2;
        menu_pos.y = (SCREEN_H / 2) + 10;

        menu_texture = surfaceToTexture(main_menu);
        continue_texture = surfaceToTexture(cont);
}

void updateGameMenu() {
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
}

void drawGameMenu(int game_outcome) {
        if(game_outcome == 0) {
                SDL_QueryTexture(continue_texture, NULL, NULL, &continue_pos.w, &continue_pos.h);
                SDL_QueryTexture(menu_texture, NULL, NULL, &menu_pos.w, &menu_pos.h);
                SDL_RenderCopy(renderer, menu_texture, NULL, &menu_pos);
                SDL_RenderCopy(renderer, continue_texture, NULL, &continue_pos);
        }
        if(game_outcome == 1) {
                SDL_QueryTexture(menu_texture, NULL, NULL, &menu_pos.w, &menu_pos.h);
                SDL_RenderCopy(renderer, menu_texture, NULL, &menu_pos);
        }
}

void cleanupGameMenu() {
        SDL_DestroyTexture(menu_texture);
        SDL_DestroyTexture(continue_texture);
}
