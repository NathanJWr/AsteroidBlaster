#ifndef BULLET_H
#define BULLET_H
#include <SDL2/SDL.h>
#include <vector>
#include "sprite.h"
typedef struct _Bullet {
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
        int hitX, hitY, hitW, hitH;
        Sprite sprite; /* Allocates Memory */
} Bullet;
Bullet makeBullet(int, int, int, int);
bool moveBullet(Bullet*);
void eraseBullet(std::vector<Bullet>&, const int);
void freeAllBullets(std::vector<Bullet>&);
#endif
