#ifndef ASTEROID_H
#define ASTEROID_H
#include <stdbool.h>
#include "sprite.h"
#include <vector>
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
        Sprite asteroid; /* Allocates Memory */
        Sprite explosion; /* Allocates Memory */
} Asteroid;

Asteroid makeAsteroid(const int SCREEN_W);
bool moveAsteroid(Asteroid*, const int SCREEN_H);
void cleanupAsteroids(std::vector<Asteroid> &);
void freeAllAsteroids(std::vector<Asteroid>&);
void eraseAsteroid(std::vector<Asteroid>&, const int);

#endif
