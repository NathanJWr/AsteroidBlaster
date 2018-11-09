#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "menu.h"
#include "display.h"
#include "gamedisplay.h"
#include "sprite.h"
extern SDL_Window* window;
extern TTF_Font* font;
extern int SCREEN_W;
extern int SCREEN_H;

void drawScore(int);
void drawPlayerLives(int);
void drawLaserPercentage(int);


SDL_Color textColor = {255, 255, 255, 255}; 
SDL_Color backgroundColor = {0, 0, 0, 255};
SDL_Rect solidRect;

struct Screen_Elements screen;

void updateGameScreen() {
  renderPresent();

  /* Reset for next frame */
  clearRender();
  renderTexture(screen.background, NULL, &screen.background_pos);
}

void drawHUD(int score,
    int lives,
    int laser_percent,
    int currency) {
  SDL_Rect pos = {15, 45, 35, 35};
  drawScore(score);
  drawPlayerLives(lives);
  drawLaserPercentage(laser_percent);
  drawPlayerCurrency(currency, &pos);
}

void drawAsteroidExplosion(Asteroid* const asteroid,
    SDL_Rect* const pos) {

  if(asteroid -> explode_iterations < 500) {
    renderSprite(&(asteroid -> explosion), pos);
    asteroid -> explode_iterations += 1;
  }
}

void drawAsteroid(Asteroid* const asteroid) {
  SDL_Color green = {144, 245, 0, 255};
  SDL_Rect pos;
  SDL_Rect hitbox;

  pos.x = asteroid -> x;
  pos.y = asteroid -> y;
  pos.w = asteroid -> sizeX;
  pos.h = asteroid -> sizeY;

  if(asteroid -> hit) {
    drawAsteroidExplosion(asteroid, &pos);
    return;
  }
  renderSprite(&(asteroid -> asteroid), &pos);
  hitbox.x = asteroid -> hitX;
  hitbox.y = asteroid -> hitY;
  hitbox.w = asteroid -> hitW;
  hitbox.h = asteroid -> hitH;
  setDrawColor(green);
  renderRectangleOutline(&hitbox);
}

void drawPlayer(Player* const player) {
  SDL_Color green = {144, 245, 0, 255};
  SDL_Rect pos;
  SDL_Rect hitbox;

  pos.x = player -> x;
  pos.y = player -> y;
  pos.w = player -> sizeX;
  pos.h = player -> sizeY;
  renderSprite(&player -> player, &pos);
  setDrawColor(green);

  hitbox.x = player -> hitX;
  hitbox.y = player -> hitY;
  hitbox.w = player -> hitW;
  hitbox.h = player -> hitH;
  renderRectangleOutline(&hitbox);
}

void drawRuby(Ruby* const ruby) {
  SDL_Rect pos;

  pos.x = ruby -> x;
  pos.y = ruby -> y;
  pos.w = ruby -> sizeX;
  pos.h = ruby -> sizeY;
  renderSprite(&ruby -> sprite, &pos);
}

void drawBullet(Bullet* const bullet) {
  SDL_Color green = {144, 245, 0, 255};
  SDL_Rect pos;
  SDL_Rect hitbox;

  pos.x = bullet -> x - bullet -> sprite.tex_rect.w / 4;;
  pos.y = bullet -> y;
  pos.w = bullet -> sizeX;
  pos.h = bullet -> sizeY;

  renderSprite(&bullet -> sprite, &pos);
  setDrawColor(green);

  hitbox.x = bullet -> hitX;
  hitbox.y = bullet -> hitY;
  hitbox.w = bullet -> hitW;
  hitbox.h = bullet -> hitH;

  renderRectangleOutline(&hitbox);
}

void cleanupGameDisplay() {
  SDL_DestroyTexture(screen.score);
  SDL_DestroyTexture(screen.background);
  SDL_DestroyTexture(screen.heart);
  SDL_DestroyTexture(screen.empty_bar);
}

void setupGameScreen() {
  screen.background = loadImageTexture("assets/images/background.png");
  screen.background_pos.x = 0;
  screen.background_pos.y = 0;
  screen.background_pos.w = SCREEN_W;
  screen.background_pos.h = SCREEN_H;

  screen.heart = loadImageTexture("assets/images/heart.png");
  screen.laser_pos.x = 10;
  screen.laser_pos.y = 5;
  screen.laser_pos.w = 96;
  screen.laser_pos.h = 30;

  screen.empty_bar = loadImageTexture("assets/images/empty_bar.png");
  screen.bar_pos.x = 5;
  screen.bar_pos.y = 5;
  screen.bar_pos.w = 110;
  screen.bar_pos.h = 32;

  screen.score = createTextTexture(font, "0", textColor);
}

void drawHorizontalBar(int percent, int x, int y,
    int w, int h, SDL_Color fg, SDL_Color bg) {

  SDL_Rect bgrect;
  SDL_Rect fgrect;

  setDrawColor(bg);
  bgrect.x = x;
  bgrect.y = y;
  bgrect.w = w;
  bgrect.h = h;
  renderRectangleFull(&bgrect);

  setDrawColor(fg);
  fgrect.x = x;
  fgrect.y = y;
  fgrect.w = percent;
  fgrect.h = h;
  renderRectangleFull(&fgrect);
}

void drawLaserPercentage(int percent) {
       SDL_Color blue = {144, 245, 0, 255};
       SDL_Color red = {255, 0, 0, 255};
       drawHorizontalBar(percent, screen.laser_pos.x,
           screen.laser_pos.y,
           screen.laser_pos.w,
           screen.laser_pos.h, blue, red);
       renderTexture(screen.empty_bar, NULL, &screen.bar_pos);
}

void drawScore(int score) {
  char result[50];
  if(screen.scor < score || screen.scor > score) {
    screen.scor = score;
    SDL_DestroyTexture(screen.score);
    sprintf(result, "%d", score);
    screen.score = createTextTexture(font, result, textColor);
  }
  SDL_QueryTexture(screen.score, NULL, NULL, &solidRect.w, &solidRect.h);
  solidRect.x = SCREEN_W / 2;
  solidRect.y = 0;
  renderTexture(screen.score, NULL, &solidRect);
}

void drawPlayerLives(int lives) {
  int offset = 50;
  int current_pos  = 0;
  int i;
  SDL_Rect heart_pos;
  heart_pos.w = 100;
  heart_pos.h = 100;
    
  for(i = 0; i < lives; i++) {
    heart_pos.x = SCREEN_W - offset * 2;
    heart_pos.y = current_pos;
    renderTexture(screen.heart, NULL, &heart_pos);
    current_pos += offset;
  }
}
