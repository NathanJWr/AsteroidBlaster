#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
struct Sprite {
        SDL_Texture* texture;
        SDL_Rect tex_rect;
        int tot_frames;
        int current_frame;
        int delay;
};
void setupAllSprites();
void renderSprite(struct Sprite*, SDL_Rect*);
void destroySprite(struct Sprite*);
void setupPlayerSprite(struct Sprite*);
void setupBulletSprite(struct Sprite*);
void setupAsteroidSprite(int, struct Sprite*, struct Sprite*);
#endif
