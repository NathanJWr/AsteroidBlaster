#ifndef UPGRADEMENU_H
#define UPGRADEMENU_H
#include <SDL2/SDL.h>
#include "player.h"
#include "menu.h"

struct UpgradeMenuAssets {
/*        SDL_Texture* laser_regen_w;
        SDL_Texture* laser_regen_y;
        SDL_Texture* laser_regen_g;
        SDL_Rect laser_pos;
        bool laser_selected;
        int laser_upgrades;
        */
        struct Button laser_upgrade;
};
int handleUpgradeMenuEvents(SDL_Event*, struct Player*);
void setupUpgradeMenu();
void drawUpgradeMenu();
void updateUpgradeMenu();
void cleanupUpgradeMenu();
#endif
