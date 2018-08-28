#include "mainmenu.h"
#include "display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
extern const int SCREEN_W;
extern const int SCREEN_H;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

struct MainMenuAssets main_menu;
SDL_Color text_color = {255, 255, 255, 255};


/*
 * Returns
 * 0 for Quit
 * 1 for Start
 * -1 for no choice
 */
int mousePressMain(SDL_MouseButtonEvent b) {
        if(b.button == SDL_BUTTON_LEFT) {
                //Start Button
                if(b.x >= main_menu.start_pos.x
                                && b.x <= main_menu.start_pos.x + main_menu.start_pos.w
                                && b.y >= main_menu.start_pos.y
                                && b.y <= main_menu.start_pos.y + main_menu.start_pos.h) {
                        return 1;
                }
                //Quit button
                else if(b.x >= main_menu.quit_pos.x
                                && b.x <= main_menu.quit_pos.x + main_menu.quit_pos.w
                                && b.y >= main_menu.quit_pos.y
                                && b.y <= main_menu.quit_pos.y + main_menu.quit_pos.h) {
                        return 0;
                }
                else return -1;
        }
        else return -1;
}
void mouseSelectMain() {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(mouse_x >= main_menu.start_pos.x
                        && mouse_x <= main_menu.start_pos.x + main_menu.start_pos.w
                        && mouse_y >= main_menu.start_pos.y
                        && mouse_y <= main_menu.start_pos.y + main_menu.start_pos.h) {
                main_menu.is_start_selected = true;
        }
        else {
                main_menu.is_start_selected = false;
        }
        if(mouse_x >= main_menu.quit_pos.x
                        && mouse_x <= main_menu.quit_pos.x + main_menu.start_pos.w
                        && mouse_y >= main_menu.quit_pos.y
                        && mouse_y <= main_menu.quit_pos.y + main_menu.start_pos.h) {
                main_menu.is_quit_selected = true;
        }
        else {
                main_menu.is_quit_selected = false;
        }
}

/*
 * Returns
 * 0 for Quit
 * 1 for Start
 * -1 for no choice
 */
int handleMainMenuEvents(SDL_Event* e) {
        int button = -1;
        while(SDL_PollEvent(e)) {
                if(e -> type == SDL_QUIT) {
                       button = 0;
                }
                else if(e -> type == SDL_MOUSEBUTTONDOWN) {
                       button = mousePressMain(e -> button);
                       return button;
                }
                else {
                        mouseSelectMain();
                }
        }
        return button;
}

void setupMainMenu() {
        main_menu.start_white = IMG_LoadTexture(renderer, "assets/start_text.png");
        main_menu.start_green = IMG_LoadTexture(renderer, "assets/start_text_green.png");
        main_menu.quit_white = IMG_LoadTexture(renderer, "assets/quit_text.png");
        main_menu.quit_green = IMG_LoadTexture(renderer, "assets/quit_text_green.png");

        main_menu.start_pos.w = 300;
        main_menu.start_pos.h = 100;
        main_menu.start_pos.x = (SCREEN_W / 2) - main_menu.start_pos.w / 2;
        main_menu.start_pos.y = (SCREEN_H / 2) - main_menu.start_pos.h / 2;

        main_menu.quit_pos.w = 300;
        main_menu.quit_pos.h = 100;
        main_menu.quit_pos.x  = (SCREEN_W / 2) - main_menu.quit_pos.w / 2;
        main_menu.quit_pos.y = (SCREEN_H / 2) - (main_menu.quit_pos.h / 2) 
                + main_menu.start_pos.h;

        main_menu.background1 = IMG_LoadTexture(renderer, "assets/background.png");
        main_menu.background2= IMG_LoadTexture(renderer, "assets/background.png");
        main_menu.background1_pos.w = SCREEN_W;
        main_menu.background1_pos.h = SCREEN_H;
        main_menu.background1_pos.x = 0;
        main_menu.background1_pos.y = 0;
        main_menu.background2_pos.w = SCREEN_W;
        main_menu.background2_pos.h = SCREEN_H;
        main_menu.background2_pos.x = 0;
        main_menu.background2_pos.y = -SCREEN_H;
        main_menu.background_offset = 0;

        main_menu.logo = IMG_LoadTexture(renderer, "assets/logo.png");
        main_menu.logo_pos.w = 810;
        main_menu.logo_pos.h = 110;
        main_menu.logo_pos.x = SCREEN_W / 2 - (main_menu.logo_pos.w / 2);
        main_menu.logo_pos.y = 150;
}
void drawMainMenu() {
        if(main_menu.is_start_selected) {
                SDL_RenderCopy(renderer, main_menu.start_green,
                                NULL, &main_menu.start_pos);
        }
        else {
                SDL_RenderCopy(renderer, main_menu.start_white,
                                NULL, &main_menu.start_pos);
        }
        if(main_menu.is_quit_selected) {
                SDL_RenderCopy(renderer, main_menu.quit_green,
                                NULL, &main_menu.quit_pos);
        }
        else {
                SDL_RenderCopy(renderer, main_menu.quit_white,
                                NULL, &main_menu.quit_pos);
        }

        SDL_RenderCopy(renderer, main_menu.logo, NULL, &main_menu.logo_pos);
}

void updateMainMenu() {
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        if(main_menu.background1_pos.y <= SCREEN_H) {
                main_menu.background1_pos.y++;
                main_menu.background2_pos.y++;
        }
        else {
                main_menu.background1_pos.y = 0;
                main_menu.background2_pos.y = -SCREEN_H;
        }
        SDL_RenderCopy(renderer, main_menu.background1, NULL, &main_menu.background1_pos);
        SDL_RenderCopy(renderer, main_menu.background2, NULL, &main_menu.background2_pos);
        SDL_Delay(10);
}

void cleanupMainMenu() {
        SDL_DestroyTexture(main_menu.start_white);
//        SDL_DestroyTexture(exit_texture);
}
