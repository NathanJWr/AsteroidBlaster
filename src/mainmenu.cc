#include "mainmenu.h"
#include "display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
extern TTF_Font* font;
extern int SCREEN_W;
extern int SCREEN_H;

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
                /* Start Button */
                if(checkBoundaries(b.x, b.y, main_menu.start.pos)) {
                        return 1;
                }
                /* Quit button */
                if(checkBoundaries(b.x, b.y, main_menu.quit.pos)) {
                        return 0;
                }
        }
        return -1;
}
void mouseSelectMain() {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(checkBoundaries(mouse_x, mouse_y, main_menu.start.pos)) {
                main_menu.start.selected = true;
        }
        else {
                main_menu.start.selected = false;
        }
        if(checkBoundaries(mouse_x, mouse_y, main_menu.quit.pos)) {
                main_menu.quit.selected = true;
        }
        else {
                main_menu.quit.selected = false;
        }
}

/*
 * Returns
 * 0 for Quit
 * 1 for Start
 * -1 for no choice
 */
int handleMainMenuEvents(SDL_Event* const e) {
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

void updateMainMenuButton(Button* const b) {
        SDL_Color white = {255, 255, 255, 255};
        SDL_Color green = {144, 245, 0, 255};
        int i;   
        for(i = 0; i < b -> num_textures; i++) {
                if(b -> textures[i] != NULL) {
                        SDL_DestroyTexture(b -> textures[i]);
                        b -> textures[i] = NULL;
                }
        }
        b -> textures[0] = createTextTexture(font,
                        b -> title, white);
        b -> textures[1] = createTextTexture(font,
                        b -> title, green);
}

void drawMainMenuButton(Button b) {
        if(b.selected) {
                renderTexture(b.textures[1], NULL, &b.pos);
        }
        else {
                renderTexture(b.textures[0], NULL, &b.pos);
        }
}

void setupMainMenu() {
        SDL_Rect start_pos;
        SDL_Rect quit_pos;

        start_pos.w = 300;
        start_pos.h = 100;
        start_pos.x = (SCREEN_W / 2) - start_pos.w / 2;
        start_pos.y = (SCREEN_H / 2) - start_pos.h / 2;
        main_menu.start = makeButton(2, start_pos);
        strcpy(main_menu.start.title, "Start");
        updateMainMenuButton(&main_menu.start);

        quit_pos.w = 300;
        quit_pos.h = 100;
        quit_pos.x = (SCREEN_W / 2) - quit_pos.w / 2;
        quit_pos.y = (SCREEN_H / 2) - (quit_pos.h / 2) + 100;
        main_menu.quit = makeButton(2, quit_pos);
        strcpy(main_menu.quit.title, "Quit");
        updateMainMenuButton(&main_menu.quit);
        

        main_menu.background1 = loadImageTexture("assets/images/background.png");
        main_menu.background2= loadImageTexture("assets/images/background.png");
        main_menu.background1_pos.w = SCREEN_W;
        main_menu.background1_pos.h = SCREEN_H;
        main_menu.background1_pos.x = 0;
        main_menu.background1_pos.y = 0;
        main_menu.background2_pos.w = SCREEN_W;
        main_menu.background2_pos.h = SCREEN_H;
        main_menu.background2_pos.x = 0;
        main_menu.background2_pos.y = -SCREEN_H;
        main_menu.background_offset = 0;

        main_menu.logo = loadImageTexture("assets/images/logo.png");
        main_menu.logo_pos.w = 810;
        main_menu.logo_pos.h = 110;
        main_menu.logo_pos.x = SCREEN_W / 2 - (main_menu.logo_pos.w / 2);
        main_menu.logo_pos.y = 150;
}
void drawMainMenu() {
        drawMainMenuButton(main_menu.start);
        drawMainMenuButton(main_menu.quit);
        renderTexture(main_menu.logo, NULL, &main_menu.logo_pos);
}

void updateMainMenu() {
        SDL_Color black = {0, 0, 0, 255};
        renderPresent();
        setDrawColor(black);
        clearRender();

        if(main_menu.background1_pos.y <= SCREEN_H) {
                main_menu.background1_pos.y++;
                main_menu.background2_pos.y++;
        }
        else {
                main_menu.background1_pos.y = 0;
                main_menu.background2_pos.y = -SCREEN_H;
        }
        renderTexture(main_menu.background1, NULL, &main_menu.background1_pos);
        renderTexture(main_menu.background2, NULL, &main_menu.background2_pos);
        SDL_Delay(10);
}

void cleanupMainMenu() {
        destroyButton(&main_menu.start);
        destroyButton(&main_menu.quit);
        SDL_DestroyTexture(main_menu.background1);
        SDL_DestroyTexture(main_menu.background2);
        SDL_DestroyTexture(main_menu.logo);
}
