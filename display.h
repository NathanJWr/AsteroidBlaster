#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
#include <stdbool.h>
        bool initVideo();
        void killVideo();
        SDL_Texture* surfaceToTexture(SDL_Surface*);
        SDL_Texture* surfaceToTextureSafe(SDL_Surface*);
#endif
