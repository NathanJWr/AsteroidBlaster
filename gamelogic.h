#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "player.h"
#include "bullet.h"
#include "block.h"
struct KeyPresses {
        bool w;
        bool a;
        bool s;
        bool d;
        bool space;
};
bool checkCollision_player(struct Block, struct Player);
bool checkCollision_bullet(struct Block, struct Bullet);
bool handleEvents(SDL_Event*, struct KeyPresses*);
void movePlayer(struct KeyPresses*, struct Player*, bulletVector*);
void gameTick(blockVector*,
                bulletVector*,
                struct Player*,
                struct KeyPresses*,
                const int);
#endif
