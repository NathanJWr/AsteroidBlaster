#ifndef CURRENCY_H
#define CURRENCY_H
#include "sprite.h"
struct Ruby {
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
        struct Sprite sprite;
};

typedef struct _rVector {
        struct Ruby* rubies;
        int size;
        int count;
} rubyVector;

struct Ruby makeRuby();
void moveRuby(struct Ruby*);
void generateCurrency(rubyVector*, int, int);

void rubyVector_init(rubyVector*);
void rubyVector_add(rubyVector*, struct Ruby);
struct Ruby* rubyVector_get(rubyVector*, int index);
void rubyVector_free(rubyVector*);
void rubyVector_erase(rubyVector*, int);
#endif
