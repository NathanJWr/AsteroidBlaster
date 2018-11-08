#include <SDL2/SDL.h>
#include <stdio.h>
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

char* loadText(std::string path, std::string title) {
        char* line = NULL;
        FILE *fp = NULL;
        char* description = NULL;
        size_t len = 0;
        size_t len2 = 0;
        fp = fopen(path.c_str(), "r");
        if(fp == NULL) {
                printf("Failed to open file %s\n", path.c_str());
        }
        while(getline(&line,&len, fp) != -1) {
                if(strstr(line, title.c_str())) {
                        if(getline(&description, &len2, fp) == -1) {
                                return NULL;
                        }
                }
        }
        fclose(fp);
        free(line);
        if(description == NULL) {
                printf("%s not found in %s\n", title.c_str(), path.c_str());
        }
        return description;
}
