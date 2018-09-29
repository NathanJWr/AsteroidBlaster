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

        int scor;
};
void updateGameScreen();
void setupGameScreen();
void drawHUD(int, int, int, int);
void drawAsteroid(Asteroid*);
void drawPlayer(Player);
void drawRuby(Ruby);
void drawBullet(Bullet);
void cleanupGameDisplay();
#endif
