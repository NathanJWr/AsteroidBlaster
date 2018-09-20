#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "display.h"
#include "gamedisplay.h"
#include "sprite.h"
extern const int SCREEN_W;
extern const int SCREEN_H;
extern SDL_Window* window;
extern TTF_Font* font;

void drawScore(int);
void drawPlayerLives(int);
void drawLaserPercentage(int);
void drawPlayerCurrency(int);


SDL_Color textColor = {255, 255, 255, 255}; //white
SDL_Color backgroundColor = {0, 0, 0, 255}; //black
SDL_Rect solidRect;

struct Screen_Elements screen;

void updateGameScreen() {
        renderPresent();

        //Reset for next frame
        clearRender();
        renderTexture(screen.background, NULL, &screen.background_pos);
}

void drawHUD(int score,
                int lives,
                int laser_percent,
                int currency) {
        drawScore(score);
        drawPlayerLives(lives);
        drawLaserPercentage(laser_percent);
        drawPlayerCurrency(currency);
}

void drawAsteroidExplosion(struct Asteroid* asteroid, SDL_Rect* pos) {
        if(asteroid -> explode_iterations < 500) {
                renderSprite(&(asteroid -> explosion), pos);
                asteroid -> explode_iterations += 1;
        }
}

void drawAsteroid(struct Asteroid* asteroid) {
        SDL_Rect pos = {
               asteroid -> x,
               asteroid -> y,
               asteroid -> sizeX,
               asteroid -> sizeY};
        if(asteroid -> hit) {
                drawAsteroidExplosion(asteroid, &pos);
                return;
        }
        renderSprite(&(asteroid -> asteroid), &pos);
        SDL_Rect hitbox = {asteroid -> hitX, asteroid -> hitY, asteroid -> hitW, asteroid -> hitH};
        SDL_Color green = {144, 245, 0};
        setDrawColor(green);
        renderRectangleOutline(&hitbox);
}

void drawPlayer(struct Player player) {
        SDL_Rect pos = {
                player.x,
                player.y,
                player.sizeX,
                player.sizeY};
        renderSprite(&player.player, &pos);
        SDL_Color green = {144, 245, 0};
        setDrawColor(green);
        SDL_Rect hitbox = {player.hitX, player.hitY, player.hitW, player.hitH};
        renderRectangleOutline(&hitbox);
}

void drawRuby(struct Ruby ruby) {
        SDL_Rect pos = {ruby.x, ruby.y, ruby.sizeX, ruby.sizeY};
        renderSprite(&ruby.sprite, &pos);
}

void drawBullet(struct Bullet bullet) {
        SDL_Rect rect = {
                bullet.x - bullet.sprite.tex_rect.w / 4,
                bullet.y,
                bullet.sizeX,
                bullet.sizeY};
        renderSprite(&bullet.sprite, &rect);
        SDL_Color green = {144, 245, 0};
        setDrawColor(green);
        SDL_Rect hitbox = {bullet.hitX, bullet.hitY, bullet.hitW, bullet.hitH};
        renderRectangleOutline(&hitbox);
}

void cleanupGameDisplay() {
        SDL_DestroyTexture(screen.score);
        SDL_DestroyTexture(screen.background);
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

        screen.ruby = loadImageTexture("assets/images/ruby_single.png");
        screen.ruby_pos.x = 5;
        screen.ruby_pos.y = 40;
        screen.ruby_pos.w = 40;
        screen.ruby_pos.h = 40;

        screen.curr = 0;
        screen.scor = 0;
        screen.currency = createTextTexture(font, "0", textColor);
        screen.score = createTextTexture(font, "0", textColor);
}

void drawHorizontalBar(int percent, int x, int y,
                int w, int h, SDL_Color fg, SDL_Color bg) {

        setDrawColor(bg);
        SDL_Rect bgrect = {x, y, w, h};
        renderRectangleFull(&bgrect);

        setDrawColor(fg);
        SDL_Rect fgrect = {x, y, percent, h};
        renderRectangleFull(&fgrect);
}

void drawLaserPercentage(int percent) {
       SDL_Color blue = {144, 245, 0, 0};
       SDL_Color red = {255, 0, 0, 0};
       drawHorizontalBar(percent, screen.laser_pos.x,
                       screen.laser_pos.y,
                       screen.laser_pos.w,
                       screen.laser_pos.h, blue, red);
       renderTexture(screen.empty_bar, NULL, &screen.bar_pos);
}

void drawScore(int score) {
        if(screen.scor < score || screen.scor > score) {
                screen.scor = score;
                SDL_DestroyTexture(screen.score);
                char result[50];
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
        for(int i = 0; i < lives; i++) {
                SDL_Rect heart_pos = {SCREEN_W - offset * 2, current_pos, 100, 100};
                renderTexture(screen.heart, NULL, &heart_pos);
                current_pos += offset;
        }
}

void drawPlayerCurrency(int currency) {
        SDL_Rect pos = {50, 45, 35, 35};
        if(screen.curr < currency || screen.curr > currency) {
                screen.curr = currency;
                SDL_DestroyTexture(screen.currency);
                char c[50];
                sprintf(c, "%d", currency);
                screen.currency = createTextTexture(font, c, textColor);
        }
        renderTexture(screen.currency, NULL, &pos);
        renderTexture(screen.ruby, NULL, &screen.ruby_pos);
}
