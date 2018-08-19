#ifndef PLAYER_H
#define PLAYER_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "sprite.h"
struct Player {
        SDL_Rect hitbox;
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
        bool hit;
        int score;
        int laser_percent;
        struct Sprite sprite;
};
struct Player makePlayer();
void playerMoveUp(struct Player*);
void playerMoveDown(struct Player*);
void playerMoveLeft(struct Player*);
void playerMoveRight(struct Player*);
void playerCleanup(struct Player*);
#endif
