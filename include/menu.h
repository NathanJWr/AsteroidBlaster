#ifndef MENU_H
#define MENU_H
#include <stdbool.h>

struct Button {
        SDL_Rect pos;
        int num_textures;
        SDL_Texture** textures;
        char title[100];
        bool selected;
};
struct Button makeButton(int, SDL_Rect);
void drawButton(struct Button);
void drawPlayerCurrency(int, SDL_Rect*);
void destroyButton(struct Button*);
bool checkBoundaries(int, int, SDL_Rect);
char* loadText(char* path, char* title);
#endif
