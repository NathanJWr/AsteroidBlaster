#ifndef DISPLAY_H
#define DISPLAY_H
#include "block.h"
#include "player.h"
#include "bullet.h"
        bool initVideo();
        void killVideo();
        SDL_Texture* surfaceToTexture(SDL_Surface*);
#endif
