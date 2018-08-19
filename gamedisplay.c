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

SDL_Color backgroundColor = {255, 255, 255, 255}; //white
SDL_Color textColor = {0, 0, 0, 255}; //black
SDL_Texture* scoreTexture;
SDL_Rect solidRect;

void updateGameScreen() {
        SDL_RenderCopy(renderer, scoreTexture, NULL, &solidRect);
        SDL_RenderPresent(renderer);

        //Reset for next frame
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_DestroyTexture(scoreTexture);
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
       int w = 100;
       int h = 30;
       int x = 0;
       int y = 0;
       SDL_Color blue = {0, 0, 255, 0};
       SDL_Color red = {255, 0, 0, 0};
       drawHorizontalBar(percent, x, y, w, h, blue, red);
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
}

void drawPlayer(struct Player player) {
        SDL_Rect pos = {
                player.x,
                player.y,
                player.sizeX,
                player.sizeY};
        renderSprite(&player.sprite, &pos);
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &player.hitbox);
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
void drawScore(int score) {
        char result[50];
        sprintf(result, "%d", score);
        SDL_Surface* solid = TTF_RenderText_Solid(font, result, textColor);
        scoreTexture = surfaceToTexture(solid);
        SDL_QueryTexture(scoreTexture, NULL, NULL, &solidRect.w, &solidRect.h);
        solidRect.x = SCREEN_W / 2;
        solidRect.y = 0;
}

void cleanupGameDisplay() {
        SDL_DestroyTexture(scoreTexture);
}
