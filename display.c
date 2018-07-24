#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "display.h"
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;
bool initVideo(const int SCREEN_W, const int SCREEN_H) {
        bool success = true;
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
                success = false;
        }
        else if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                printf("Linear filtering not enabled!");
        }
        window = SDL_CreateWindow("Game",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        SCREEN_W,
                        SCREEN_H,
                        SDL_WINDOW_SHOWN);
        if(window == NULL) {
                success = false;
        }
        else {
                renderer = SDL_CreateRenderer(window,
                                -1,
                                SDL_RENDERER_ACCELERATED);
                if(renderer == NULL) {
                        success = false;
                }
                else {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
        IMG_Init(IMG_INIT_PNG);
        return success;
}

void killVideo() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);

        renderer = NULL;
        window = NULL;
        
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
}

SDL_Texture* surfaceToTexture(SDL_Surface* surf) {
        SDL_Texture* text;
        text = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        return text;
}

