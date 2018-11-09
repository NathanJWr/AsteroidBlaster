#include "asteroid.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <vector>
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

void cleanupAsteroids(std::vector<Asteroid> &asteroids) {
        unsigned int i;
        for(i = 0; i < asteroids.size(); i++) {
                destroySprite(&(asteroids[i].asteroid));
                destroySprite(&(asteroids[i].explosion));
        }
}

void eraseAsteroid(std::vector<Asteroid> &vec, const int index) {
        destroySprite(&vec[index].asteroid);  
        destroySprite(&vec[index].explosion);  
        vec.erase(vec.begin() + index);
}

void freeAllAsteroids(std::vector<Asteroid> &vec) {
        for(Asteroid &n : vec) {
                destroySprite(&n.asteroid);
                destroySprite(&n.explosion);
        }
        vec.clear();
}
