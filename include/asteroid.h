#ifndef ASTEROID_H
#define ASTEROID_H
#include <stdbool.h>
#include "sprite.h"
struct Asteroid {
        int sprite_num;
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
        bool hit;
        int hitX, hitY, hitW, hitH;
        int explode_iterations;
        struct Sprite asteroid;
        struct Sprite explosion;
};

typedef struct _bVector {
        struct Asteroid* asteroids;
        int size;
        int count;
} asteroidVector;

struct Asteroid makeAsteroid(const int SCREEN_W);
bool moveAsteroid(struct Asteroid*, const int SCREEN_H);


void asteroidVector_init(asteroidVector*);
void asteroidVector_add(asteroidVector*, struct Asteroid);
struct Asteroid* asteroidVector_get(asteroidVector*, int index);
void asteroidVector_free(asteroidVector*);
void asteroidVector_erase(asteroidVector*, int);

#endif