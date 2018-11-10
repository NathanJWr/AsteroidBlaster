#ifndef UPGRADEMENU_H
#define UPGRADEMENU_H
#include <SDL2/SDL.h>
#include <string>
#include "player.h"
#include "menu.h"
typedef struct _UpgradeButton {
  Button button;
  bool upgraded;
  std::string mouseover_text;
  int clicked;
  int max_clicks;
  int cost;
} UpgradeButton;
struct UpgradeMenuAssets {
  SDL_Texture* ruby;
  SDL_Texture* currency;
  UpgradeButton laser_upgrade;
  UpgradeButton laser_cost;
  UpgradeButton move_speed;
  UpgradeButton laser_split;
	Button exit;
  bool quit;
};
int handleUpgradeMenuEvents(SDL_Event*, Player*);
void setupUpgradeMenu();
void drawUpgradeMenu(int);
void updateUpgradeMenu();
void cleanupUpgradeMenu();
void resetUpgradeMenu();
#endif
