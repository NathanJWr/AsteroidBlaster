#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"
#include "display.h"
extern SDL_Renderer* renderer;

void renderSprite(struct Sprite* sprite, SDL_Rect* pos) {
        sprite -> current_frame = (SDL_GetTicks() / sprite -> delay) % sprite -> tot_frames;
        sprite -> tex_rect.x = sprite -> current_frame * sprite -> tex_rect.w;
        SDL_RenderCopy(renderer, sprite -> texture, &(sprite -> tex_rect), pos);
}

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

void destroySprite(struct Sprite* sprite) {
        SDL_DestroyTexture(sprite -> texture);
}

void setupPlayerSprite(struct Sprite* player) {
        player -> texture = IMG_LoadTexture(renderer, "assets/ship.png");
        querySprite(player);
}

void setupBulletSprite(struct Sprite* bullet) {
        bullet -> texture = IMG_LoadTexture(renderer, "assets/laser.png");
        querySprite(bullet);
}

void setupAsteroidSprite(int type, struct Sprite* asteroid,
        struct Sprite* explosion) {

        if(type == 1) {
               asteroid -> texture = IMG_LoadTexture(renderer,
                        "assets/asteroid1.png");

               explosion -> texture = IMG_LoadTexture(renderer,
                        "assets/asteroid1_explode.png");
        }
        else if(type == 2) {
                asteroid -> texture = IMG_LoadTexture(renderer,
                         "assets/asteroid2.png");

                explosion -> texture = IMG_LoadTexture(renderer,
                         "assets/asteroid2_explode.png");
        }
        else if(type == 3) {
                asteroid -> texture = IMG_LoadTexture(renderer,
                         "assets/asteroid3.png");

                explosion -> texture = IMG_LoadTexture(renderer,
                         "assets/asteroid3_explode.png");
        }
        querySprite(asteroid);
        querySprite(explosion);
        explosion -> delay = 200;
}
