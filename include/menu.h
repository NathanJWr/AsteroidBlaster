#ifndef MENU_H
#define MENU_H
#include <stdbool.h>

struct Button {
        bool selected;
        bool upgraded;
        SDL_Rect pos;
        int num_textures;
        SDL_Texture** textures;
        char mouseover_text[999];
        char title[100];
        int clicked;
        int max_clicks;
};
struct Button makeButton(int, int, SDL_Rect);
void destroyButton(struct Button*);
bool checkBoundaries(int, int, SDL_Rect);
#endif
