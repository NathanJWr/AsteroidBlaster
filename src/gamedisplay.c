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
extern SDL_Renderer* renderer;
extern TTF_Font* font;

void drawScore(int);
void drawPlayerLives(int);
void drawLaserPercentage(int);


SDL_Color textColor = {255, 255, 255, 255}; //white
SDL_Color backgroundColor = {0, 0, 0, 255}; //black
SDL_Rect solidRect;

struct Screen_Elements screen;

void updateGameScreen() {
        SDL_RenderCopy(renderer, screen.score, NULL, &solidRect);
        SDL_RenderPresent(renderer);

        //Reset for next frame
        SDL_RenderClear(renderer);
        SDL_DestroyTexture(screen.score);
        SDL_RenderCopy(renderer, screen.background, NULL, &screen.background_pos);
}

void drawHUD(int score, int lives, int laser_percent) {
        drawScore(score);
        drawPlayerLives(lives);
        drawLaserPercentage(laser_percent);
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
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &hitbox);
}

void drawPlayer(struct Player player) {
        SDL_Rect pos = {
                player.x,
                player.y,
                player.sizeX,
                player.sizeY};
        renderSprite(&player.player, &pos);
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect hitbox = {player.hitX, player.hitY, player.hitW, player.hitH};
        SDL_RenderDrawRect(renderer, &hitbox);
}

void drawBullet(struct Bullet bullet) {
        bullet.sprite.current_frame = (SDL_GetTicks() / bullet.sprite.delay) % bullet.sprite.tot_frames;
        bullet.sprite.tex_rect.x = bullet.sprite.current_frame * bullet.sprite.tex_rect.w;
        SDL_Rect rect = {
                bullet.x - bullet.sprite.tex_rect.w / 4,
                bullet.y,
                bullet.sizeX,
                bullet.sizeY};
        SDL_RenderCopy(renderer, bullet.sprite.texture, &bullet.sprite.tex_rect, &rect);
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect hitbox = {bullet.hitX, bullet.hitY, bullet.hitW, bullet.hitH};
        SDL_RenderDrawRect(renderer, &hitbox);
}

void cleanupGameDisplay() {
        SDL_DestroyTexture(screen.score);
        SDL_DestroyTexture(screen.background);
}

void setupGameScreen() {
        screen.background = IMG_LoadTexture(renderer, "assets/background.png");
        screen.background_pos.x = 0;
        screen.background_pos.y = 0;
        screen.background_pos.w = SCREEN_W;
        screen.background_pos.h = SCREEN_H;

        screen.heart = IMG_LoadTexture(renderer, "assets/heart.png");
        screen.laser_pos.x = 10;
        screen.laser_pos.y = 5;
        screen.laser_pos.w = 96;
        screen.laser_pos.h = 30;

        screen.empty_bar = IMG_LoadTexture(renderer, "assets/empty_bar.png");
        screen.bar_pos.x = 5;
        screen.bar_pos.y = 5;
        screen.bar_pos.w = 110;
        screen.bar_pos.h = 32;

}

void drawHorizontalBar(int percent, int x, int y,
                int w, int h, SDL_Color fg, SDL_Color bg) {

        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
        SDL_Rect bgrect = {x, y, w, h};
        SDL_RenderFillRect(renderer, &bgrect);

        SDL_SetRenderDrawColor(renderer, fg.r, fg.g, fg.b, fg.a);
        SDL_Rect fgrect = {x, y, percent, h};
        SDL_RenderFillRect(renderer, &fgrect);
}

void drawLaserPercentage(int percent) {
       SDL_Color blue = {144, 245, 0, 0};
       SDL_Color red = {255, 0, 0, 0};
       drawHorizontalBar(percent, screen.laser_pos.x,
                       screen.laser_pos.y,
                       screen.laser_pos.w,
                       screen.laser_pos.h, blue, red);
       renderTexture(screen.empty_bar, &screen.bar_pos);
}

void drawScore(int score) {
        char result[50];
        sprintf(result, "%d", score);
        screen.score = createTextTexture(font, result, textColor);
        SDL_QueryTexture(screen.score, NULL, NULL, &solidRect.w, &solidRect.h);
        solidRect.x = SCREEN_W / 2;
        solidRect.y = 0;
}

void drawPlayerLives(int lives) {
        int offset = 50;
        int current_pos  = 0;
        for(int i = 0; i < lives; i++) {
                SDL_Rect heart_pos = {SCREEN_W - offset * 2, current_pos, 100, 100};
                renderTexture(screen.heart, &heart_pos);
                current_pos += offset;
        }
}
