#include <SDL2/SDL.h>
#include <stdbool.h>
#include "display.h"
#include "block.h"
#include "bullet.h"
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
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
        return success;
}
void updateScreen() {
        SDL_RenderPresent(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
        SDL_RenderClear(gRenderer);
}
void killVideo() {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);

        gRenderer = NULL;
        gWindow = NULL;
        
        SDL_Quit();
}

void drawBlock(struct Block block) {
        SDL_SetRenderDrawColor(gRenderer, 102, 255, 102, 0xFF);
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

