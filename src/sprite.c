#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"
#include "display.h"
extern SDL_Renderer* renderer;
SDL_Surface* player;
SDL_Surface* asteroid1;
SDL_Surface* asteroid2;
SDL_Surface* asteroid3;
SDL_Surface* asteroid1_exp;
SDL_Surface* asteroid2_exp;
SDL_Surface* asteroid3_exp;
SDL_Surface* bullet;
SDL_Surface* heart;

void querySprite(struct Sprite* sprite) {
        SDL_QueryTexture(sprite -> texture,
                        NULL,
                        NULL,
                        &(sprite -> tex_rect.w),
                        &(sprite -> tex_rect.h));
        sprite -> tot_frames = sprite -> tex_rect.w / sprite -> tex_rect.h;
        sprite -> tex_rect.w /= sprite -> tot_frames;
        sprite -> tex_rect.x = 0;
        sprite -> tex_rect.y = 0;
        sprite -> delay = 100;
}
void setupAllSprites() {
        player = loadImageSurface("assets/ship.png");
        asteroid1 = loadImageSurface("assets/asteroid1.png");
        asteroid2 = loadImageSurface("assets/asteroid2.png");
        asteroid3 = loadImageSurface("assets/asteroid3.png");
        asteroid1_exp = loadImageSurface("assets/asteroid1_explode.png");
        asteroid2_exp = loadImageSurface("assets/asteroid2_explode.png");
        asteroid3_exp = loadImageSurface("assets/asteroid3_explode.png");
        bullet = loadImageSurface("assets/laser.png");
        heart = loadImageSurface("assets/heart.png");
}
void renderSprite(struct Sprite* sprite, SDL_Rect* pos) {
        if(sprite -> texture == NULL) {
                printf("Texture not loaded\n");
                exit(1);
        }
        sprite -> current_frame = (SDL_GetTicks() / sprite -> delay) % sprite -> tot_frames;
        sprite -> tex_rect.x = sprite -> current_frame * sprite -> tex_rect.w;
        renderTexture(sprite -> texture, &(sprite -> tex_rect), pos);
}

void destroySprite(struct Sprite* sprite) {
        if(sprite -> texture != NULL) {
                SDL_DestroyTexture(sprite -> texture);
                sprite -> texture = NULL;
        }
}

void setupHeartSprite(struct Sprite* h) {
        h -> texture = surfaceToTextureSafe(heart);
        querySprite(h);
}

void setupPlayerSprite(struct Sprite* p) {
        p -> texture = surfaceToTextureSafe(player);
        querySprite(p);
}

void setupBulletSprite(struct Sprite* b) {
        b -> texture = surfaceToTextureSafe(bullet);
        querySprite(b);
}

void setupAsteroidSprite(int type, struct Sprite* asteroid,
        struct Sprite* explosion) {

        if(type == 1) {
                asteroid -> texture = surfaceToTextureSafe(asteroid1);
                explosion -> texture = surfaceToTextureSafe(asteroid1_exp);
        }
        else if(type == 2) {
                asteroid -> texture = surfaceToTextureSafe(asteroid2);
                explosion -> texture = surfaceToTextureSafe(asteroid2_exp);
        }
        else if(type == 3) {
                asteroid -> texture = surfaceToTextureSafe(asteroid3);
                explosion -> texture = surfaceToTextureSafe(asteroid3_exp);
        }
        querySprite(asteroid);
        querySprite(explosion);
}

void cleanupSpriteSurfaces() {
        SDL_FreeSurface(player);
        SDL_FreeSurface(asteroid1);
        SDL_FreeSurface(asteroid2);
        SDL_FreeSurface(asteroid3);
        SDL_FreeSurface(asteroid1_exp);
        SDL_FreeSurface(asteroid2_exp);
        SDL_FreeSurface(asteroid3_exp);
        SDL_FreeSurface(bullet);
        SDL_FreeSurface(heart);
}
