#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "display.h"
#include "gamedisplay.h"
extern const int SCREEN_W;
extern const int SCREEN_H;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

SDL_Color backgroundColor = {255, 255, 255, 255}; //white
SDL_Color textColor = {0, 0, 0, 255}; //black
SDL_Texture* scoreTexture;
SDL_Rect solidRect;

struct Sprite playerT;
struct Sprite projectile;
struct Sprite asteroid1;
struct Sprite asteroid2;
struct Sprite asteroid1_exp;
struct Sprite asteroid2_exp;
//struct Sprite asteroid_3;

void querySprite(struct Sprite* sprite) {
        SDL_QueryTexture(sprite -> texture,
                        NULL,
                        NULL,
                        &(sprite -> tex_rect.w),
                        &(sprite -> tex_rect.h));
        sprite -> tot_frames = sprite -> tex_rect.w / sprite -> tex_rect.h;
        sprite -> tex_rect.w /= sprite -> tot_frames;
        sprite -> delay = 100;
}
void setupGameSprites() {
        //Player
        playerT.texture = IMG_LoadTexture(renderer, "assets/ship.png");
        querySprite(&playerT);

        //projectile
        projectile.texture = IMG_LoadTexture(renderer, "assets/laser.png");
        querySprite(&projectile);

        //asteroid
        asteroid1.texture = IMG_LoadTexture(renderer, "assets/asteroid1.png");
        querySprite(&asteroid1);

        asteroid2.texture = IMG_LoadTexture(renderer, "assets/asteroid2.png");
        querySprite(&asteroid2);

        //asteroid explosions
        asteroid1_exp.texture = IMG_LoadTexture(renderer, "assets/asteroid1_explode.png");
        querySprite(&asteroid1_exp);

        asteroid2_exp.texture = IMG_LoadTexture(renderer, "assets/asteroid2_explode.png");
        querySprite(&asteroid2_exp);

        //asteroid_3.texture = IMG_LoadTexture(renderer, "assets/asteroid3.png");
        //querySprite(&asteroid_3);
}

void updateGameScreen() {
        SDL_RenderCopy(renderer, scoreTexture, NULL, &solidRect); 
        SDL_RenderPresent(renderer);

        //Reset for next frame
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
}

void renderSprite(struct Sprite* sprite, SDL_Rect* pos) {
        sprite -> current_frame = (SDL_GetTicks() / sprite -> delay) % sprite -> tot_frames;
        sprite -> tex_rect.x = sprite -> current_frame * sprite -> tex_rect.w;
        SDL_RenderCopy(renderer, sprite -> texture, &(sprite -> tex_rect), pos);
}
void drawAsteroidExplosion(struct Asteroid asteroid, SDL_Rect* pos) {
        if(asteroid.sprite_num == 1) {
                renderSprite(&asteroid1_exp, pos);
        }
        if(asteroid.sprite_num == 2) {
                renderSprite(&asteroid2_exp, pos);
        }
}
void drawAsteroid(struct Asteroid asteroid) {
        SDL_Rect pos = {
               asteroid.x,
               asteroid.y,
               asteroid.sizeX,
               asteroid.sizeY};
        if(asteroid.hit) {
                SDL_SetRenderDrawColor(renderer, 102, 255, 102, 0xFF);
                drawAsteroidExplosion(asteroid, &pos);
                return;
        }
        else {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
        }
        if(asteroid.sprite_num == 1) {
                renderSprite(&asteroid1, &pos);
        }
        else if(asteroid.sprite_num == 2) {
                renderSprite(&asteroid2, &pos);
        }
        SDL_Rect hitbox = {asteroid.hitX, asteroid.hitY, asteroid.hitW, asteroid.hitH};
        SDL_RenderDrawRect(renderer, &hitbox);
}

void drawPlayer(struct Player player) {
        SDL_Rect pos = {
                player.x,
                player.y,
                player.sizeX,
                player.sizeY};
        renderSprite(&playerT, &pos);
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);		    
        SDL_RenderDrawRect(renderer, &player.hitbox);
}

void drawBullet(struct Bullet bullet) {
        projectile.current_frame = (SDL_GetTicks() / projectile.delay) % projectile.tot_frames;
        projectile.tex_rect.x = projectile.current_frame * projectile.tex_rect.w;
        SDL_Rect rect = {
                bullet.x - projectile.tex_rect.w / 4,
                bullet.y,
                bullet.sizeX,
                bullet.sizeY};
        SDL_RenderCopy(renderer, projectile.texture, &projectile.tex_rect, &rect);
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
        SDL_DestroyTexture(playerT.texture);
        SDL_DestroyTexture(projectile.texture);
        SDL_DestroyTexture(asteroid1.texture);
        SDL_DestroyTexture(asteroid2.texture);
        SDL_DestroyTexture(asteroid1_exp.texture);
        SDL_DestroyTexture(asteroid2_exp.texture);
        //SDL_DestroyTexture(asteroid_3.texture);
}
