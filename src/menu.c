#include <SDL2/SDL.h>
#include <stdio.h>
#include "menu.h"
struct Button makeButton(int num_textures, SDL_Rect pos) {
        struct Button button;
        button.selected = false;
        button.pos = pos;
        button.num_textures = num_textures;
        button.textures = malloc(num_textures * sizeof(SDL_Texture*));
        return button;
}

void destroyButton(struct Button* button) {
       for(int i = 0; i < button -> num_textures; i++) {
               SDL_DestroyTexture(button -> textures[i]);
       }
       free(button -> textures);
}


bool checkBoundaries(int x, int y, SDL_Rect rect) {
        if(x >= rect.x
                        && x <= rect.x + rect.w
                        && y >= rect.y
                        && y <= rect.y + rect.h) {
                return true;
        }
        else return false;
}
