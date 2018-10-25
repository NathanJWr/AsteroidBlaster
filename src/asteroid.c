#include "asteroid.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
Asteroid makeAsteroid(const int SCREEN_W) {
        Asteroid b;
        b.sprite_num = (rand() % 3) + 1;
        b.x = rand() % SCREEN_W;
        b.y = 0;
        b.sizeX = (rand() % 31) + 30;
        b.sizeY = b.sizeX;
        b.dy = 0;
        while(b.dy == 0) {
                b.dy = (rand() % 3) + 1;
        }
        b.hit = false;
        b.hitX = b.x; 
        b.hitY = b.y;
        b.hitW = b.sizeX;
        b.hitH = b.sizeY;
        b.explode_iterations = 0;
        setupAsteroidSprite(b.sprite_num, &b.asteroid, &b.explosion);
        b.explosion.delay = 300;
        return b;
}

bool moveAsteroid(Asteroid* const asteroid, const int SCREEN_H) {
        asteroid -> y += asteroid -> dy;
        asteroid -> hitY += asteroid -> dy;
        if(asteroid -> y > SCREEN_H) {
                return false;
        }
        else return true;
}

void asteroidVector_init(asteroidVector* const v) {
        v->asteroids = NULL;
        v->size = 0;
        v->count = 0;
}

void asteroidVector_add(asteroidVector* const v, Asteroid b) {
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

Asteroid* asteroidVector_get(asteroidVector* const v, int index) {
        if(index >= v->size || index < 0) {
                exit(1);
        }
        return &(v->asteroids[index]);
}

void asteroidVector_erase(asteroidVector* const v, int index) {
        int i;
        if(index >= v->size || index < 0) {
                exit(1);
        }
        destroySprite(&(v -> asteroids[index].asteroid));
        destroySprite(&(v -> asteroids[index].explosion));
        for(i = index; i < v -> count; i++) {
                v -> asteroids[i] = v -> asteroids[i+1];
        }
        v -> count--;
}

void asteroidVector_free(asteroidVector* const v) {
        int i;
        for(i = 0; i < v -> count; i++) {
                destroySprite(&(v -> asteroids[i].asteroid));
                destroySprite(&(v -> asteroids[i].explosion));
        }
        free(v->asteroids);
        v->size = 0;
        v->count = 0;
}
