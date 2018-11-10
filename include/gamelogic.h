#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "player.h"
#include "bullet.h"
#include "asteroid.h"
#include "currency.h"
struct KeyPresses {
  bool w;
  bool a;
  bool s;
  bool d;
  bool space;
  bool escape;
};
bool checkCollision_player(Asteroid, Player);
bool checkCollision_bullet(Asteroid, Bullet);
bool checkCollision_ruby(Ruby r, Player p);
bool handleEvents(SDL_Event*, struct KeyPresses*);
void gameTick(std::vector<Asteroid>&,
              std::vector<Bullet>&,
              std::vector<Ruby>&,
              Player*,
              struct KeyPresses*,
              const int);
#endif
