#ifndef BULLET_H
#define BULLET_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "sprite.h"
struct Bullet {
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
        int hitX, hitY, hitW, hitH;
        struct Sprite sprite;
};

typedef struct _bulletVector {
        struct Bullet* bullets;
        int size;
        int count;
} bulletVector;

struct Bullet makeBullet(int, int, int, int);
bool moveBullet(struct Bullet*, const int);
void bulletVector_init(bulletVector*);
void bulletVector_add(bulletVector*, struct Bullet);
struct Bullet bulletVector_get(bulletVector*, int);
void bulletVector_free(bulletVector*);
void bulletVector_erase(bulletVector*, int);
#endif
