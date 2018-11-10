#ifndef MENU_H
#define MENU_H
#include <stdbool.h>
#include <string>

typedef struct _Button {
  SDL_Rect pos;
  int num_textures;
  SDL_Texture** textures;
  char title[100];
  bool selected;
} Button;
Button makeButton(int, SDL_Rect);
void setButtonTextures(SDL_Color colors[], Button*, char*);
void drawButton(Button);
void drawPlayerCurrency(int, SDL_Rect*);
void destroyButton(Button*);
bool checkBoundaries(int, int, SDL_Rect);
//char* loadText(std::string path, std::string title);
std::string loadText(std::string path, std::string title);
#endif
