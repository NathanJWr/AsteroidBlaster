#ifndef MENU_H
#define MENU_H
#include <stdbool.h>

struct Button {
        bool selected;
        SDL_Rect pos;
        int num_textures;
        SDL_Texture** textures;
};
struct Button makeButton(int, SDL_Rect);
void destroyButton(struct Button*);
bool checkBoundaries(int, int, SDL_Rect);
#endif
