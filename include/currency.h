#ifndef CURRENCY_H
#define CURRENCY_H
#include "sprite.h"
#include <stdbool.h>
typedef struct _Ruby {
  int x;
  int y;
  int dx;
  int dy;
  int sizeX;
  int sizeY;
  Sprite sprite;
} Ruby;

typedef struct _rVector {
  Ruby* rubies;
  int size;
  int count;
} rubyVector;

Ruby makeRuby();
bool moveRuby(Ruby*);
void generateCurrency(rubyVector*, int, int);

void rubyVector_init(rubyVector*);
void rubyVector_add(rubyVector*, Ruby);
Ruby* rubyVector_get(rubyVector*, int index);
void rubyVector_free(rubyVector*);
void rubyVector_erase(rubyVector*, int);
#endif
