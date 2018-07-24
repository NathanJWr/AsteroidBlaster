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
void setupGameSprites() {
        //Player
        playerT.texture = IMG_LoadTexture(renderer, "assets/ship.png");
        SDL_QueryTexture(playerT.texture,
                        NULL,
                        NULL,
                        &playerT.tex_rect.w,
                        &playerT.tex_rect.h);
        playerT.tot_frames = playerT.tex_rect.w / playerT.tex_rect.h;
        playerT.tex_rect.w /= playerT.tot_frames;
        playerT.delay = 100;

        //projectile
        projectile.texture = IMG_LoadTexture(renderer, "assets/laser.png");
        SDL_QueryTexture(projectile.texture,
                        NULL,
                        NULL,
                        &projectile.tex_rect.w,
                        &projectile.tex_rect.h);
        projectile.tot_frames = projectile.tex_rect.w / projectile.tex_rect.h;
        projectile.tex_rect.w /= projectile.tot_frames;
        projectile.delay = 100;
}

void updateGameScreen() {
        SDL_RenderCopy(renderer, scoreTexture, NULL, &solidRect); 
        SDL_RenderPresent(renderer);

        //Reset for next frame
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
}
void drawBlock(struct Block block) {
        if(block.hit) {
                SDL_SetRenderDrawColor(renderer, 102, 255, 102, 0xFF);
        }
        else {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
        }
        SDL_Rect rect = {
               block.x,
               block.y,
               block.sizeX,
               block.sizeY};
        SDL_RenderFillRect(renderer, &rect);
}

void drawPlayer(struct Player player) {
        playerT.current_frame = (SDL_GetTicks() / playerT.delay) % playerT.tot_frames;
        playerT.tex_rect.x = playerT.current_frame * playerT.tex_rect.w;
        SDL_Rect pos = {
                player.x,
                player.y,
                player.sizeX,
                player.sizeY};
        SDL_RenderCopy(renderer, playerT.texture, &playerT.tex_rect, &pos);
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
}
