#ifndef UPGRADEMENU_H
#define UPGRADEMENU_H
#include <SDL2/SDL.h>
#include "player.h"
#include "menu.h"
struct UpgradeButton {
        struct Button button;
        bool upgraded;
        char mouseover_text[999];
        int clicked;
        int max_clicks;
        int cost;
};
struct UpgradeMenuAssets {
        SDL_Texture* ruby;
        SDL_Texture* currency;
        struct UpgradeButton laser_upgrade;
        struct UpgradeButton laser_cost;
        struct UpgradeButton move_speed;
        struct UpgradeButton laser_split;
};
int handleUpgradeMenuEvents(SDL_Event*, struct Player*);
void setupUpgradeMenu();
void drawUpgradeMenu(int);
void updateUpgradeMenu();
void cleanupUpgradeMenu();
void resetUpgradeMenu();
#endif
