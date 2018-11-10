#ifndef CURRENCY_H
#define CURRENCY_H
#include "sprite.h"
#include <vector>
typedef struct _Ruby {
  int x;
  int y;
  int dx;
  int dy;
  int sizeX;
  int sizeY;
  Sprite sprite;
} Ruby;

Ruby makeRuby();
bool moveRuby(Ruby*);
void generateCurrency(std::vector<Ruby>&, int, int);

void eraseRuby(std::vector<Ruby>&, const int index);
void freeAllRubies(std::vector<Ruby>&);
#endif
