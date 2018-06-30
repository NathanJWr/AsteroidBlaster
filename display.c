#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "display.h"
SDL_Window* gWindow;
SDL_Renderer* gRenderer;

TTF_Font* font;
SDL_Color textColor = {255, 255, 255, 255}; //white
SDL_Color backgroundColor = {0, 0, 0, 255}; //black
SDL_Texture* solidTexture;
SDL_Rect solidRect;

bool initVideo(const int SCREEN_W, const int SCREEN_H) {
        bool success = true;
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
                success = false;
        }
        else if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                printf("Linear filtering not enabled!");
        }
        gWindow = SDL_CreateWindow("Game",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        SCREEN_W,
                        SCREEN_H,
                        SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
                success = false;
        }
        else {
                gRenderer = SDL_CreateRenderer(gWindow,
                                -1,
                                SDL_RENDERER_ACCELERATED);
                if(gRenderer == NULL) {
                        success = false;
                }
                else {
                        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                }
        }
        //setup TTF
        if(TTF_Init() == -1) {
                printf("Failed to initialize TTF: %s\n", SDL_GetError());
                success = false;
        }
        font = TTF_OpenFont("Ubuntu.ttf", 90);
        if(font == NULL) {
                printf("Failed to load font: %s\n", SDL_GetError());
                success = false;
        }
        return success;
}
void updateScreen() {
        SDL_RenderCopy(gRenderer, solidTexture, NULL, &solidRect); 
        SDL_RenderPresent(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
        SDL_RenderClear(gRenderer);
}
void killVideo() {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        TTF_CloseFont(font);
        SDL_DestroyTexture(solidTexture); 

        gRenderer = NULL;
        gWindow = NULL;
        
        SDL_Quit();
}

void drawBlock(struct Block block) {
        if(block.hit) {
                SDL_SetRenderDrawColor(gRenderer, 102, 255, 102, 0xFF);
        }
        else {
                SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0xFF);
        }
        SDL_Rect rect = {
               block.x,
               block.y,
               block.sizeX,
               block.sizeY};
        SDL_RenderFillRect(gRenderer, &rect);
}

void drawPlayer(struct Player player) {
        SDL_SetRenderDrawColor(gRenderer,238,130,238,0xFF);
        SDL_Rect rect = {
                player.x,
                player.y,
                player.sizeX,
                player.sizeY};
        SDL_RenderFillRect(gRenderer, &rect);
}

void drawBullet(struct Bullet bullet) {
        SDL_SetRenderDrawColor(gRenderer,238,130,238,0xFF);
        SDL_Rect rect = {
                bullet.x,
                bullet.y,
                bullet.sizeX,
                bullet.sizeY};
        SDL_RenderFillRect(gRenderer, &rect);
}

SDL_Texture* surfaceToTexture(SDL_Surface* surf) {
        SDL_Texture* text;
        text = SDL_CreateTextureFromSurface(gRenderer, surf);
        SDL_FreeSurface(surf);
        return text;
}

void drawScore(int score) {
        char result[50];
        sprintf(result, "%d", score);
        SDL_Surface* solid = TTF_RenderText_Solid(font, result, textColor);
        solidTexture = surfaceToTexture(solid);
        SDL_QueryTexture(solidTexture, NULL, NULL, &solidRect.w, &solidRect.h);
        solidRect.x = 0;
        solidRect.y = 0;
}

