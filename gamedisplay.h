#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include "asteroid.h"
#include "player.h"
#include "bullet.h"
#include <SDL2/SDL.h>
struct Sprite {
        SDL_Texture* texture;
        SDL_Rect tex_rect;
        int tot_frames;
        int current_frame;
        int delay;
};

void setupGameSprites();
void updateGameScreen();
void drawAsteroid(struct Asteroid);
void drawPlayer(struct Player);
void drawBullet(struct Bullet);
void drawScore(int);
void cleanupGameDisplay();
#endif
