#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include "asteroid.h"
#include "player.h"
#include "bullet.h"
#include <SDL2/SDL.h>
void updateGameScreen();
void setupGameScreen();
void drawLaserPercentage(int);
void drawAsteroid(struct Asteroid*);
void drawPlayer(struct Player);
void drawBullet(struct Bullet);
void drawScore(int);
void cleanupGameDisplay();
#endif
