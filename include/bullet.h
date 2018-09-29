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

typedef struct _bulletVector {
        Bullet* bullets;
        int size;
        int count;
} bulletVector;

Bullet makeBullet(int, int, int, int);
bool moveBullet(Bullet*);
void bulletVector_init(bulletVector*);
void bulletVector_add(bulletVector*, Bullet);
Bullet bulletVector_get(bulletVector*, int);
void bulletVector_free(bulletVector*);
void bulletVector_erase(bulletVector*, int);
#endif
