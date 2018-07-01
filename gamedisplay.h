#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include "block.h"
#include "player.h"
#include "bullet.h"
void updateGameScreen();
void drawBlock(struct Block);
void drawPlayer(struct Player);
void drawBullet(struct Bullet);
void drawScore(int);
void cleanupGameDisplay();
#endif
