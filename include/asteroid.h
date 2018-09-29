#ifndef ASTEROID_H
#define ASTEROID_H
#include <stdbool.h>
#include "sprite.h"
typedef struct _Asteroid {
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
        Sprite asteroid;
        Sprite explosion;
} Asteroid;

typedef struct _bVector {
        Asteroid* asteroids;
        int size;
        int count;
} asteroidVector;

Asteroid makeAsteroid(const int SCREEN_W);
bool moveAsteroid(Asteroid*, const int SCREEN_H);


void asteroidVector_init(asteroidVector*);
void asteroidVector_add(asteroidVector*, Asteroid);
Asteroid* asteroidVector_get(asteroidVector*, int index);
void asteroidVector_free(asteroidVector*);
void asteroidVector_erase(asteroidVector*, int);

#endif
