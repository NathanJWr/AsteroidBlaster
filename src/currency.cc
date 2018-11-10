#include "currency.h"
#include "sprite.h"
#include <stdlib.h>
#include <string.h>
extern int SCREEN_H;
Ruby makeRuby(int x, int y) {
  Ruby ruby;
  ruby.x = x;
  ruby.y = y;
  ruby.dy = 2;
  ruby.dx = 0;
  ruby.sizeX = 30;
  ruby.sizeY = 30;
  setupRubySprite(&ruby.sprite);
  return ruby;
}

bool moveRuby(Ruby* const r) {
  r -> y += r -> dy;
  if(r -> y > SCREEN_H) {
    return false;
  }
  else return true;
}

void generateCurrency(std::vector<Ruby> &v, int x, int y) {
  int p = rand() % 100 + 1;
  if(p >= 70) {
    v.push_back(makeRuby(x,y));
  }
}

void eraseRuby(std::vector<Ruby>& vec, const int index) {
  destroySprite(&vec[index].sprite);
  vec.erase(vec.begin() + index);
}

void freeAllRubies(std::vector<Ruby> &vec) {
  for(Ruby &r : vec) {
    destroySprite(&r.sprite);
  }
  vec.clear();
}
