#include "mainmenu.h"
#include "display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
extern const int SCREEN_W;
extern const int SCREEN_H;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

SDL_Texture* start_texture;
SDL_Texture* exit_texture;
SDL_Rect start_pos;
SDL_Rect quit_pos;
SDL_Color text_color = {255, 255, 255, 255};

int start_w;
int start_h;
int quit_w;
int quit_h;

int mousePressMain(SDL_MouseButtonEvent b) {
        if(b.button == SDL_BUTTON_LEFT) {
                //Start Button
                if(b.x >= start_pos.x
                                && b.x <= start_pos.x + start_w
                                && b.y >= start_pos.y
                                && b.y <= start_pos.y + start_h) {
                        return 1;
                }
                //Quit button
                else if(b.x >= quit_pos.x
                                && b.x <= quit_pos.x + quit_w
                                && b.y >= quit_pos.y
                                && b.y <= quit_pos.y + quit_h) {
                        return 0;
                }
                else return -1;
        }
        else return -1;
}
/*
 * Returns
 * 0 for Quit
 * 1 for Start
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
        }
        return -1;
}

void setupMainMenu() {
        SDL_Surface* start = TTF_RenderText_Solid(font, "Start", text_color);
        SDL_Surface* quit = TTF_RenderText_Solid(font, "Quit", text_color);

        start_w = start -> w;
        start_h = start -> h;
        quit_w = quit -> w;
        quit_h = quit -> h;

        start_texture = surfaceToTexture(start);
        exit_texture = surfaceToTexture(quit);

        start_pos.x = (SCREEN_W / 2) - 100;
        start_pos.y = (SCREEN_H / 2) - 100;
        quit_pos.x = (SCREEN_W / 2) - 100;
        quit_pos.y = (SCREEN_H / 2) + 10;
}
void drawMainMenu() {
        SDL_QueryTexture(start_texture, NULL, NULL, &start_pos.w, &start_pos.h);
        SDL_QueryTexture(exit_texture, NULL, NULL, &quit_pos.w, &quit_pos.h);
        SDL_RenderCopy(renderer, start_texture, NULL, &start_pos);
        SDL_RenderCopy(renderer, exit_texture, NULL, &quit_pos);
}

void updateMainMenu() {
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
}

void cleanupMainMenu() {
        SDL_DestroyTexture(start_texture);
        SDL_DestroyTexture(exit_texture);
}
