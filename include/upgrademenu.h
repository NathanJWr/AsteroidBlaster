#ifndef UPGRADEMENU_H
#define UPGRADEMENU_H
#include <SDL2/SDL.h>
#include "player.h"
#include "menu.h"

struct UpgradeMenuAssets {
        struct Button laser_upgrade;
        struct Button move_speed;
};
int handleUpgradeMenuEvents(SDL_Event*, struct Player*);
void setupUpgradeMenu();
void drawUpgradeMenu();
void updateUpgradeMenu();
void cleanupUpgradeMenu();
#endif
