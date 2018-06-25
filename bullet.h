#ifndef BULLET_H
#define BULLET_H
#include <stdbool.h>
struct Bullet {
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
};

typedef struct _bulletVector {
        struct Bullet* bullets;
        int size;
        int count;
} bulletVector;

struct Bullet makeBullet(int, int);
bool moveBullet(struct Bullet*, const int);
void bulletVector_init(bulletVector*);
void bulletVector_add(bulletVector*, struct Bullet);
void bulletVector_free(bulletVector*);
void bulletVector_erase(bulletVector*, int);

#endif