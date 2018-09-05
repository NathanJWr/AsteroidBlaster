#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "upgrademenu.h"
#include "display.h"
#include "menu.h"
#include "player.h"
extern TTF_Font* font;
struct UpgradeMenuAssets up_menu; 
void updateUpgradeButton(struct Button* button);
bool updateTimesClicked(struct Button* button);
Player_Upgrades mousePressUpgrades(SDL_MouseButtonEvent b);
void mouseSelectUpgrades();
void drawUpgradeButton(struct Button button);
void drawUpgradeText(struct Button button);
char* loadText(char* path, char* title);

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

void setupUpgradeMenu() {
        char* path = "assets/text/upgrades.txt";

        SDL_Rect laser_pos = {0, 0, 350, 50};
        up_menu.laser_upgrade = makeButton(3, 3, laser_pos); 
        strcpy(up_menu.laser_upgrade.title,
                        "Laser Regeneration (%d/%d)");
        updateUpgradeButton(&up_menu.laser_upgrade);
        strcpy(up_menu.laser_upgrade.mouseover_text,
                        loadText(path, "Laser Regeneration"));

        SDL_Rect moveSpeed_pos = {0, 50, 300, 50};
        up_menu.move_speed = makeButton(3, 3, moveSpeed_pos);
        strcpy(up_menu.move_speed.title, "Move Speed (%d/%d)");
        updateUpgradeButton(&up_menu.move_speed);
        strcpy(up_menu.move_speed.mouseover_text,
                        loadText(path, "Move Speed"));
}

void drawUpgradeMenu() {
        drawUpgradeButton(up_menu.laser_upgrade);
        drawUpgradeButton(up_menu.move_speed);
        drawUpgradeText(up_menu.laser_upgrade);
        drawUpgradeText(up_menu.move_speed);
}

void updateUpgradeMenu() {
        renderPresent();
        SDL_Color black = {0, 0, 0};
        setDrawColor(black);
        clearRender();
        SDL_Delay(10);
}

void cleanupUpgradeMenu() {
        for(int i = 0; i < up_menu.laser_upgrade.num_textures; i++) {
                SDL_DestroyTexture(up_menu.laser_upgrade.textures[i]);
        }
        for(int i = 0; i < up_menu.move_speed.num_textures; i++) {
                SDL_DestroyTexture(up_menu.move_speed.textures[i]);
        }
}

bool updateTimesClicked(struct Button* button) {
        if(button -> clicked < button -> max_clicks) {
                button -> clicked++;
                return true;
        }
        else return false;
}

Player_Upgrades mousePressUpgrades(SDL_MouseButtonEvent b) {
        if(b.button == SDL_BUTTON_LEFT) {
                if(checkBoundaries(b.x, b.y, up_menu.laser_upgrade.pos)) {

                        bool upgrade = 
                                updateTimesClicked(&up_menu.laser_upgrade);
                        updateUpgradeButton(&up_menu.laser_upgrade);
                        if(upgrade) {
                                return LASER_REGEN;
                        }
                        else return NONE;
                }
                if(checkBoundaries(b.x, b.y, up_menu.move_speed.pos)) {
                        bool u = updateTimesClicked(&up_menu.move_speed);
                        updateUpgradeButton(&up_menu.move_speed);
                        if(u) {
                                return MOVE_SPEED;
                        }
                        else return NONE;
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
        if(checkBoundaries(mouse_x, mouse_y, up_menu.move_speed.pos)) {
                up_menu.move_speed.selected = true;
        }
        else {
                up_menu.move_speed.selected = false;
        }
}

void drawUpgradeButton(struct Button button) {
        if(button.selected) {
                if(button.upgraded) {
                        renderTexture(button.textures[2],
                                        NULL, &button.pos);
                }
                else {
                        renderTexture(button.textures[1],
                                        NULL, &button.pos);
                }
        }
        else {
                renderTexture(button.textures[0],
                                NULL, &button.pos);
        }
}

void drawUpgradeText(struct Button button) {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(button.selected) {
                renderTextBox(mouse_x, mouse_y, button.mouseover_text);
        }
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

void updateUpgradeButton(struct Button* button) {
        SDL_Color white = {255, 255, 255};
        SDL_Color green = {144, 245, 0};
        SDL_Color yellow = {255, 255, 0};
        
        for(int i = 0; i < button -> num_textures; i++) {
                if(button -> textures[i] != NULL) {
                        SDL_DestroyTexture(button -> textures[i]);
                }
        }
        
        char buffer[100];
        strcpy(buffer,button -> title); 
        sprintf(buffer, button -> title, button -> clicked, button -> max_clicks);
        
        button -> textures[0] = createTextTexture(font,
                        buffer, white);
        button -> textures[1] = createTextTexture(font,
                        buffer, yellow);
        button -> textures[2] = createTextTexture(font,
                        buffer, green);
}
