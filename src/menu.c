#include <SDL2/SDL.h>
#include <stdio.h>
#include "menu.h"
#include "display.h"
struct Button makeButton(int num_textures, SDL_Rect pos) {
        struct Button button;
        button.selected = false;
        button.pos = pos;
        button.num_textures = num_textures;
        button.textures = malloc(num_textures * sizeof(SDL_Texture*));
        for(int i = 0; i < num_textures; i++) {
                button.textures[i] = NULL;
        }
        return button;
}

void destroyButton(struct Button* button) {
       for(int i = 0; i < button -> num_textures; i++) {
               SDL_DestroyTexture(button -> textures[i]);
               button -> textures[i] = NULL;
       }
       free(button -> textures);
}
void drawButton(struct Button button) {
        if(button.selected) {
                renderTexture(button.textures[1], NULL, &button.pos);
        }
        else {
                renderTexture(button.textures[0], NULL, &button.pos);
        }
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
