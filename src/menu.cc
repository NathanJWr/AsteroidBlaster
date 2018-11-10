#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "menu.h"
#include "display.h"
extern TTF_Font* font;
int menu_currency;
bool currency_init;
Button makeButton(int num_textures, SDL_Rect pos) {
  int i;
  Button button;
  button.selected = false;
  button.pos = pos;
  button.num_textures = num_textures;
  button.textures = (SDL_Texture**) malloc(num_textures * sizeof(SDL_Texture*));
  for(i = 0; i < num_textures; i++) {
    button.textures[i] = NULL;
  }
  return button;
}

void setButtonTextures(SDL_Color* colors, Button* button, char* title) {
  /* 
  The number of colors and number of textures
  better be the same size
  */
  int i;
  for(i = 0; i < button->num_textures; i++) {
    if(button->textures[i] != NULL) {
      SDL_DestroyTexture(button->textures[i]);
    }
    button -> textures[i] = createTextTexture(font, title, colors[i]);
  }
}

void destroyButton(Button* const button) {
       int i;
       for(i = 0; i < button -> num_textures; i++) {
         SDL_DestroyTexture(button -> textures[i]);
         button -> textures[i] = NULL;
       }
       free(button -> textures);
}

void drawButton(Button button) {
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

std::string loadText(std::string path, std::string title) {
  std::ifstream file(path); 
  std::string line;
  if(!file) {
    std::cout << "Failed to open file " << path << std::endl;
  }
  while(line != title) {
    std::getline(file, line);
  }
  std::getline(file, line);
  file.close();
  return line;
}
