#ifndef DISPLAY_H
#define DISPLAY_H
#include "block.h"
#include "player.h"
#include "bullet.h"
        bool initVideo();
        void updateScreen();
        void killVideo();
        void drawBlock(struct Block);
        void drawPlayer(struct Player);
        void drawBullet(struct Bullet);
        void drawScore(int);
//        SDL_Texture* surfaceToTexture(SDL_Surface*)
#endif
