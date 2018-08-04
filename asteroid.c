#include "asteroid.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct Asteroid makeAsteroid(const int SCREEN_W) {
        struct Asteroid b;
        b.sprite_num = (rand() % 3) + 1;
        b.x = rand() % SCREEN_W;
        b.y = 0;
        b.sizeX = (rand() % 31) + 30;
        b.sizeY = b.sizeX; 
        b.dy = 0;
        while(b.dy == 0) {
                b.dy = (rand() % 1) + 1;
        }
        b.hit = false;
        b.hitX = b.x - 5;
        b.hitY = b.y;
        b.hitW = b.sizeX;
        b.hitH = b.sizeY;
        return b;
}

bool moveAsteroid(struct Asteroid* asteroid, const int SCREEN_H) {
        asteroid -> y += asteroid -> dy;
        asteroid -> hitY += asteroid -> dy;
        if(asteroid -> y > SCREEN_H) {
                return false;
        }
        else return true;
}

void asteroidVector_init(asteroidVector* v) {
        v->asteroids = NULL;
        v->size = 0;
        v->count = 0;
}

void asteroidVector_add(asteroidVector* v, struct Asteroid b) {
        if(v->size == 0) {
                v->size = 10;
                v->asteroids = malloc(sizeof(b) * v->size);
                memset(v->asteroids, '\0', sizeof(b) * v->size);
        }
        if(v->size == v->count) {
                v->size *= 2;
                v->asteroids = realloc(v->asteroids, sizeof(b) * v->size);
        }
        v->asteroids[v->count] = b;
        v->count++;
}

struct Asteroid* asteroidVector_get(asteroidVector* v, int index) {
        if(index >= v->size || index < 0) {
                exit(1);
        }
        return &(v->asteroids[index]);
}

void asteroidVector_erase(asteroidVector* v, int index) {
        if(index >= v->size || index < 0) {
                exit(1);
        }
        v->asteroids[index] = makeAsteroid(1024);
}

void asteroidVector_free(asteroidVector* v) {
        free(v->asteroids);
        v->size = 0;
        v->count = 0;
}
