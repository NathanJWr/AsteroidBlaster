#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "display.h"
extern const int SCREEN_W;
extern const int SCREEN_H;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

SDL_Color backgroundColor = {255, 255, 255, 255}; //white
SDL_Color textColor = {0, 0, 0, 255}; //black
SDL_Texture* scoreTexture;
SDL_Rect solidRect;

SDL_Texture* player_texture;
SDL_Rect player_tex_rect;
int player_frames;
int pframe;
int pdelay = 100;
void setupGameSprites(char* player_file) {
        int w, h;
        player_texture = IMG_LoadTexture(renderer, player_file);
        SDL_QueryTexture(player_texture, NULL, NULL, &player_tex_rect.w, &player_tex_rect.h);
        player_frames = player_tex_rect.w / player_tex_rect.h;
        player_tex_rect.w /= player_frames;
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
        pframe = (SDL_GetTicks() / pdelay) % player_frames;
        player_tex_rect.x = pframe * player_tex_rect.w;
        SDL_Rect pos = {
                player.x,
                player.y,
                player.sizeX,
                player.sizeY};
        SDL_RenderCopy(renderer, player_texture, &player_tex_rect, &pos);
}

void drawBullet(struct Bullet bullet) {
        SDL_SetRenderDrawColor(renderer,238,130,238,0xFF);
        SDL_Rect rect = {
                bullet.x,
                bullet.y,
                bullet.sizeX,
                bullet.sizeY};
        SDL_RenderFillRect(renderer, &rect);
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
        SDL_DestroyTexture(player_texture);
}
