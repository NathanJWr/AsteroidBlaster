#ifndef PLAYER_H
#define PLAYER_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "sprite.h"
typedef enum  {
        LASER_REGEN,
        MOVE_SPEED,
        NONE

} Player_Upgrades;
struct Player {
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
        bool hit;
        int score;
        int hitX;
        int hitY;
        int hitW;
        int hitH;
        int laser_percent;
        int lives;
        struct Sprite player;
        struct Sprite heart;

        //Upgrades
        int laser_regen;
        int move_speed;
};
struct Player makePlayer();
void playerHandleUpgrades(Player_Upgrades, struct Player* player);
void playerMoveUp(struct Player*);
void playerMoveDown(struct Player*);
void playerMoveLeft(struct Player*);
void playerMoveRight(struct Player*);
void playerCleanup(struct Player*);

#endif
