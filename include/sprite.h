#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
typedef struct _Sprite {
  SDL_Texture* texture;
  SDL_Rect tex_rect;
  int tot_frames;
  int current_frame;
  int delay;
} Sprite;
void setupAllSprites();
void renderSprite(Sprite*, SDL_Rect*);
void destroySprite(Sprite*);
void setupHeartSprite(Sprite*);
void setupPlayerSprite(Sprite*);
void setupBulletSprite(Sprite*);
void setupRubySprite(Sprite*);
void setupAsteroidSprite(int, Sprite*, Sprite*);
void cleanupSpriteSurfaces();
#endif
