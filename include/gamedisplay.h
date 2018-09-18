#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H
#include "asteroid.h"
#include "player.h"
#include "bullet.h"
#include "currency.h"
#include <SDL2/SDL.h>
struct Screen_Elements {
        SDL_Texture* heart;
        SDL_Texture* score;
        SDL_Texture* background;
        SDL_Texture* empty_bar;
        SDL_Rect background_pos;
        SDL_Rect laser_pos;
        SDL_Rect bar_pos;
        SDL_Color blue;
        SDL_Color red;
};
void updateGameScreen();
void setupGameScreen();
void drawHUD(int, int, int);
void drawAsteroid(struct Asteroid*);
void drawPlayer(struct Player);
void drawRuby(struct Ruby);
void drawBullet(struct Bullet);
void cleanupGameDisplay();
#endif
