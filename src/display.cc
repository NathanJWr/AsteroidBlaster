#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdbool.h>
#include "display.h"
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;
extern int SCREEN_W;
extern int SCREEN_H;
TTF_Font* ubuntu;
struct Display_Objects displayObs;
bool initVideo() {
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

        if(TTF_Init() == -1) {
                printf("Failed to initialize TTF: %s\n", SDL_GetError());
                success = false;
        }
        font = TTF_OpenFont("assets/fonts/prstart.ttf", 90);
        ubuntu = TTF_OpenFont("assets/fonts/Ubuntu.ttf", 12);

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
        TTF_CloseFont(ubuntu);

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
}

SDL_Texture* surfaceToTexture(SDL_Surface* const surf) {
        SDL_Texture* text = NULL;
        text = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);

        if(text == NULL) {
                printf("Texture Creation Error: %s\n", SDL_GetError());
        }
        return text;
}

SDL_Texture* surfaceToTextureSafe(SDL_Surface* const surf) {
        SDL_Texture* text = NULL;
        text = SDL_CreateTextureFromSurface(renderer, surf);

        if(text == NULL) {
                printf("Texture Creation Error: %s\n", SDL_GetError());
                return NULL;
        }
        return text;
}

SDL_Texture* createTextTexture(TTF_Font* const font,
                std::string text,
                SDL_Color color) {
        
        SDL_Surface* surface = NULL;
        SDL_Texture* texture = NULL;
        surface = TTF_RenderText_Solid(font, text.c_str(), color);

        if(surface == NULL) {
                printf("Text Render Error: %s\n", TTF_GetError());
                return NULL;
        }

        texture = surfaceToTexture(surface);
        return texture;
}
SDL_Texture* createTextTextureWrapped(TTF_Font* const font,
                std::string text,
                SDL_Color color,
                int length) {

        SDL_Surface* surf = NULL;
        SDL_Texture* tex = NULL;
        surf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, length);
        if(surf == NULL) {
                printf("Text Render Error: %s\n", TTF_GetError());
                return NULL;
        }
        tex = surfaceToTexture(surf);
        return tex;
}

SDL_Texture* loadImageTexture(std::string path) {
        SDL_Texture* tex = NULL;
        tex = IMG_LoadTexture(renderer, path.c_str());

        if(tex == NULL) {
                printf("Image Load Error: %s\n", IMG_GetError());
                return NULL;
        }
        return tex;
}

SDL_Surface* loadImageSurface(std::string path) {
        SDL_Surface* surface = NULL;
        surface = IMG_Load(path.c_str());

        if(surface == NULL) {
                printf("Image Load Error: %s\n", IMG_GetError());
                return NULL;
        }
        return surface;
}

void renderTextBox(int x, int y, char text[]) {
        int w, h;
        SDL_Color white;
        SDL_Color black;
        SDL_Rect text_box;
        SDL_Texture* tex;

        white.r = 255;
        white.g = 255;
        white.b = 255;
        white.a = 0;

        black.r = 0;
        black.g = 0;
        black.b = 0;
        black.a = 0;
        
        tex = createTextTextureWrapped(ubuntu, text, white, 400);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        text_box.x = x;
        text_box.y = y;
        text_box.w = w;
        text_box.h = h;

        setDrawColor(black);
        renderRectangleFull(&text_box);
        setDrawColor(white);
        renderRectangleOutline(&text_box);
        renderTexture(tex, NULL, &text_box);
        SDL_DestroyTexture(tex);
}

void initDisplayObjects() {
        displayObs.ruby = loadImageTexture("assets/images/ruby_single.png");
        displayObs.curr = NULL;
        displayObs.currency = 0;
}

void cleanDisplayObjects() {
        SDL_DestroyTexture(displayObs.ruby);
        SDL_DestroyTexture(displayObs.curr);
}

void drawPlayerCurrency(int currency, SDL_Rect* const pos) {
        SDL_Color white = {255, 255, 255, 0};
        SDL_Rect pos1 ;
        pos1.x = pos -> x + 50;
        pos1.y = pos -> y;
        pos1.w = pos -> w;
        pos1.h = pos -> h;
        if(displayObs.currency == 0 
                        || displayObs.currency < currency 
                        || displayObs.currency > currency) {
                char c[50];
                displayObs.currency = currency;
                SDL_DestroyTexture(displayObs.curr);
                sprintf(c, "%d", currency);
                displayObs.curr = createTextTexture(font, c, white);
        }
        renderTexture(displayObs.curr, NULL, &pos1);
        renderTexture(displayObs.ruby, NULL, pos);
}
        

void renderTexture(SDL_Texture* const texture,
                SDL_Rect* const source,
                SDL_Rect* const destination) {

        SDL_RenderCopy(renderer, texture, source, destination);
}

void setDrawColor(SDL_Color color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void renderRectangleOutline(SDL_Rect* const rect) {
        SDL_RenderDrawRect(renderer, rect);
}

void renderRectangleFull(SDL_Rect* const rect) {
        SDL_RenderFillRect(renderer, rect);
}

void renderPresent() {
        SDL_RenderPresent(renderer);
}

void clearRender() {
        SDL_RenderClear(renderer);
}
