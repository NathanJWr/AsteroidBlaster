#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "upgrademenu.h"
#include "display.h"
#include "menu.h"
#include "player.h"
extern TTF_Font* font;
struct UpgradeMenuAssets up_menu; 

Player_Upgrades mousePressUpgrades(SDL_MouseButtonEvent b) {
        if(b.button == SDL_BUTTON_LEFT) {
                if(checkBoundaries(b.x, b.y, up_menu.laser_upgrade.pos)) {
                        return LASER_REGEN;
                }
        }
        return -1;

}

void mouseSelectUpgrades() {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(checkBoundaries(mouse_x, mouse_y, up_menu.laser_upgrade.pos)) {
                up_menu.laser_upgrade.selected = true;
        }
        else {
                up_menu.laser_upgrade.selected = false;
        }
}
int handleUpgradeMenuEvents(SDL_Event* e, struct Player* p) {
        int button = -1;
        while(SDL_PollEvent(e)) {
                if(e -> type == SDL_QUIT) {
                        button = 0;
                }
                else if(e -> type == SDL_MOUSEBUTTONDOWN) {
                        playerHandleUpgrades(mousePressUpgrades(e -> button), p);
                }
                else {
                        mouseSelectUpgrades();
                }
        }
        
        return button;
}

void drawUpgradeMenu() {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(up_menu.laser_upgrade.selected) {
                renderTexture(up_menu.laser_upgrade.textures[1], NULL, &up_menu.laser_upgrade.pos);
                renderTextBox(mouse_x, mouse_y, up_menu.laser_upgrade.mouseover_text);
        }
        else {
                renderTexture(up_menu.laser_upgrade.textures[0], NULL, &up_menu.laser_upgrade.pos);
        }
}

void updateUpgradeMenu() {
        renderPresent();
        SDL_Color black = {0, 0, 0};
        setDrawColor(black);
        clearRender();
}
char* loadText(char* path, char* title) {
        FILE *fp = NULL;
        fp = fopen(path, "r");
        if(fp == NULL) {
                printf("Failed to open file %s\n", path);
        }
        char* line = NULL;
        char* description = NULL;
        size_t len = 0;
        size_t len2 = 0;
        while(getline(&line,&len, fp) != -1) {
                if(strstr(line, title)) {
                        getline(&description, &len2, fp); 
                }
        }
        fclose(fp);
        if(description == NULL) {
                printf("%s not found in %s\n", title, path);
        }
        return description;
}
void setupUpgradeMenu() {
        SDL_Color white = {255, 255, 255};
        SDL_Color green = {144, 245, 0};
        SDL_Color yellow = {255, 255, 0};
        char* path = "assets/text/upgrades.txt";

        SDL_Rect laser_pos = {0, 0, 300, 50};
        up_menu.laser_upgrade = makeButton(3, laser_pos); 
        up_menu.laser_upgrade.textures[0] = createTextTexture(font,
                        "Laser Regeneration", white);
        up_menu.laser_upgrade.textures[1] = createTextTexture(font,
                        "Laser Regeneration", yellow);
        up_menu.laser_upgrade.textures[2] = createTextTexture(font,
                        "Laser Regeneration", green);
        up_menu.laser_upgrade.mouseover_text = loadText(path, "Laser Upgrade");
}
