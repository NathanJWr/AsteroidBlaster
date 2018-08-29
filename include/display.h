#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
        bool initVideo();
        void killVideo();
        SDL_Texture* surfaceToTexture(SDL_Surface*);
        SDL_Texture* surfaceToTextureSafe(SDL_Surface*);
        SDL_Texture* createTextTexture(TTF_Font*, char*, SDL_Color);
        SDL_Texture* loadImageTexture(char*);
        SDL_Surface* loadImageSurface(char*);
        void renderTexture(SDL_Texture*, SDL_Rect*);
#endif
