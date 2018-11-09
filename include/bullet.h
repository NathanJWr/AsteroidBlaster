#ifndef BULLET_H
#define BULLET_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "sprite.h"
typedef struct _Bullet {
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
        int hitX, hitY, hitW, hitH;
        Sprite sprite;
} Bullet;
Bullet makeBullet(int, int, int, int);
bool moveBullet(Bullet*);
#endif
