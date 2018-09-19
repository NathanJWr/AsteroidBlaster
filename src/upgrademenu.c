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
void updateUpgradeButton(struct UpgradeButton* button);
bool updateTimesClicked(struct UpgradeButton* button, struct Player* p);
Player_Upgrades mousePressUpgrades(SDL_MouseButtonEvent b, struct Player* p);
void mouseSelectUpgrades();
void drawUpgradeButton(struct UpgradeButton button);
void drawUpgradeText(struct UpgradeButton button);
struct UpgradeButton makeUpgradeButton(int, int, SDL_Rect);

int handleUpgradeMenuEvents(SDL_Event* e, struct Player* p) {
        int button = -1;
        while(SDL_PollEvent(e)) {
                if(e -> type == SDL_QUIT) {
                        button = 0;
                }
                else if(e -> type == SDL_MOUSEBUTTONDOWN) {
                        playerHandleUpgrades(mousePressUpgrades(e -> button, p), p);
                }
                else {
                        mouseSelectUpgrades();
                }
        }
        
        return button;
}

void setupUpgradeMenu() {
        char* path = "assets/text/upgrades.txt";

        /* laser_upgrade  */
        SDL_Rect laser_pos = {0, 0, 350, 50};
        up_menu.laser_upgrade = makeUpgradeButton(3, 3, laser_pos); 
        strcpy(up_menu.laser_upgrade.button.title,
                        "Laser Regeneration (%d/%d)");
        updateUpgradeButton(&up_menu.laser_upgrade);
        strcpy(up_menu.laser_upgrade.mouseover_text,
                        loadText(path, "Laser Regeneration"));
        up_menu.laser_upgrade.cost = 5;

        /* laser_cost */
        SDL_Rect laserCost_pos = {0, 50, 300, 50};
        up_menu.laser_cost = makeUpgradeButton(3, 3, laserCost_pos);
        strcpy(up_menu.laser_cost.button.title,
                        "Laser Cost (%d/%d)");
        updateUpgradeButton(&up_menu.laser_cost);
        strcpy(up_menu.laser_cost.mouseover_text,
                        loadText(path, "Laser Cost"));
        up_menu.laser_cost.cost = 5;

        /* move_speed */
        SDL_Rect moveSpeed_pos = {0, 100, 300, 50};
        up_menu.move_speed = makeUpgradeButton(3, 3, moveSpeed_pos);
        strcpy(up_menu.move_speed.button.title, "Move Speed (%d/%d)");
        updateUpgradeButton(&up_menu.move_speed);
        strcpy(up_menu.move_speed.mouseover_text,
                        loadText(path, "Move Speed"));
        up_menu.move_speed.cost = 15;

        /* laser_split */
        SDL_Rect laserSplit_pos = {0, 150, 300, 50};
        up_menu.laser_split = makeUpgradeButton(3, 1, laserSplit_pos);
        strcpy(up_menu.laser_split.button.title, "Laser Split (%d/%d)");
        updateUpgradeButton(&up_menu.laser_split);
        strcpy(up_menu.laser_split.mouseover_text,
                        loadText(path, "Laser Split"));
        up_menu.laser_split.cost = 25;
}

void drawUpgradeMenu() {
        drawUpgradeButton(up_menu.laser_upgrade);
        drawUpgradeButton(up_menu.laser_cost);
        drawUpgradeButton(up_menu.move_speed);
        drawUpgradeButton(up_menu.laser_split);
        drawUpgradeText(up_menu.laser_upgrade);
        drawUpgradeText(up_menu.laser_cost);
        drawUpgradeText(up_menu.move_speed);
        drawUpgradeText(up_menu.laser_split);
}

void updateUpgradeMenu() {
        renderPresent();
        SDL_Color black = {0, 0, 0};
        setDrawColor(black);
        clearRender();
        SDL_Delay(10);
}

void cleanupUpgradeMenu() {
        for(int i = 0; i < up_menu.laser_upgrade.button.num_textures; i++) {
                SDL_DestroyTexture(up_menu.laser_upgrade.button.textures[i]);
        }
        for(int i = 0; i < up_menu.move_speed.button.num_textures; i++) {
                SDL_DestroyTexture(up_menu.move_speed.button.textures[i]);
        }
}
void resetUpgradeMenu() {
        up_menu.laser_upgrade.clicked = 0;
        up_menu.laser_split.clicked = 0;
        up_menu.move_speed.clicked = 0;
        cleanupUpgradeMenu();
}

bool updateTimesClicked(struct UpgradeButton* button, struct Player* p) {
        if(button -> clicked < button -> max_clicks
                        && p -> currency >= button -> cost) {
                button -> clicked++;
                p -> currency -= button -> cost;
                return true;
        }
        else return false;
}

Player_Upgrades mousePressUpgrades(SDL_MouseButtonEvent b, struct Player* p) {
        if(b.button == SDL_BUTTON_LEFT) {
                if(checkBoundaries(b.x,
                        b.y,
                        up_menu.laser_upgrade.button.pos)) {

                        bool u = 
                                updateTimesClicked(&up_menu.laser_upgrade, p);
                        updateUpgradeButton(&up_menu.laser_upgrade);
                        if(u) {
                                return LASER_REGEN;
                        }
                        else return NONE;
                }
                if(checkBoundaries(b.x,
                        b.y,
                        up_menu.laser_cost.button.pos)) {

                        bool u = updateTimesClicked(&up_menu.laser_cost, p);
                        updateUpgradeButton(&up_menu.laser_cost);
                        if(u) {
                                return LASER_COST;
                        }
                        else return NONE;
                }
                if(checkBoundaries(b.x,
                        b.y,
                        up_menu.move_speed.button.pos)) {

                        bool u = updateTimesClicked(&up_menu.move_speed, p);
                        updateUpgradeButton(&up_menu.move_speed);
                        if(u) {
                                return MOVE_SPEED;
                        }
                        else return NONE;
                }
                if(checkBoundaries(b.x,
                        b.y,
                        up_menu.laser_split.button.pos)) {

                        bool u = updateTimesClicked(&up_menu.laser_split, p);
                        updateUpgradeButton(&up_menu.laser_split);
                        if(u) {
                                return LASER_SPLIT;
                        }
                        else return NONE;
                }
        }
        return NONE;
}

void mouseSelectUpgrades() {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(checkBoundaries(mouse_x, mouse_y, up_menu.laser_upgrade.button.pos)) {
                up_menu.laser_upgrade.button.selected = true;
        }
        else {
                up_menu.laser_upgrade.button.selected = false;
        }
        if(checkBoundaries(mouse_x, mouse_y, up_menu.laser_cost.button.pos)) {
                up_menu.laser_cost.button.selected = true;
        }
        else {
                up_menu.laser_cost.button.selected = false;
        }
        if(checkBoundaries(mouse_x, mouse_y, up_menu.move_speed.button.pos)) {
                up_menu.move_speed.button.selected = true;
        }
        else {
                up_menu.move_speed.button.selected = false;
        }
        if(checkBoundaries(mouse_x, mouse_y, up_menu.laser_split.button.pos)) {
                up_menu.laser_split.button.selected = true;
        }
        else {
                up_menu.laser_split.button.selected = false;
        }
}

void drawUpgradeButton(struct UpgradeButton b) {
        if(b.button.selected) {
                if(b.upgraded) {
                        renderTexture(b.button.textures[2],
                                        NULL, &b.button.pos);
                }
                else {
                        renderTexture(b.button.textures[1],
                                        NULL, &b.button.pos);
                }
        }
        else {
                renderTexture(b.button.textures[0],
                                NULL, &b.button.pos);
        }
}

void drawUpgradeText(struct UpgradeButton b) {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(b.button.selected) {
                renderTextBox(mouse_x, mouse_y, b.mouseover_text);
        }
}

void updateUpgradeButton(struct UpgradeButton* b) {
        SDL_Color white = {255, 255, 255};
        SDL_Color green = {144, 245, 0};
        SDL_Color yellow = {255, 255, 0};
        
        for(int i = 0; i < b -> button.num_textures; i++) {
                if(b -> button.textures[i] != NULL) {
                        SDL_DestroyTexture(b -> button.textures[i]);
                }
        }
        
        char buffer[100];
        strcpy(buffer, b -> button.title); 
        sprintf(buffer, b -> button.title, b -> clicked, b -> max_clicks);
        
        b -> button.textures[0] = createTextTexture(font,
                        buffer, white);
        b -> button.textures[1] = createTextTexture(font,
                        buffer, yellow);
        b -> button.textures[2] = createTextTexture(font,
                        buffer, green);
}

struct UpgradeButton makeUpgradeButton(int num_tex, int max_clicks, SDL_Rect pos) {
        struct UpgradeButton u;
        u.upgraded = false;
        u.max_clicks = max_clicks;
        u.clicked = 0;

        u.button = makeButton(num_tex, pos);
        return u;
}
