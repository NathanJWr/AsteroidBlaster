#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include "upgrademenu.h"
#include "display.h"
#include "menu.h"
#include "player.h"
extern TTF_Font* font;
struct UpgradeMenuAssets up_menu; 
void updateUpgradeButton(UpgradeButton &button);
bool updateTimesClicked(UpgradeButton* button, Player* p);
void mousePressUpgrades(SDL_MouseButtonEvent b, Player* p);
void mouseSelectUpgrades();
void drawUpgradeButton(UpgradeButton button);
void drawUpgradeText(UpgradeButton button);
UpgradeButton makeUpgradeButton(int, int, SDL_Rect);

int handleUpgradeMenuEvents(SDL_Event* const e, Player* const p) {
  int button = -1;
  while(SDL_PollEvent(e)) {
    if(e -> type == SDL_QUIT || up_menu.quit) {
      button = 0;
      up_menu.quit = false;
    }
    else if(e -> type == SDL_MOUSEBUTTONDOWN) {
      //playerHandleUpgrades(mousePressUpgrades(e -> button, p), p);
      mousePressUpgrades(e->button, p);
    }
    else {
      mouseSelectUpgrades();
    }
  }
  return button;
}

void setupUpgradeMenu() {
  std::string path = "assets/text/upgrades.txt";
  std::string text;
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color green = {144, 245, 0, 255};

  SDL_Rect laser_pos = {0, 0, 350, 50};
  SDL_Rect laserCost_pos = {0, 50, 300, 50};
  SDL_Rect moveSpeed_pos = {0, 100, 300, 50};
  SDL_Rect laserSplit_pos = {0, 150, 300, 50};
	SDL_Rect exit_pos = {0, 200, 150, 50};

  SDL_Color colors[2];
  colors[0] = white;
  colors[1] = green;

  /* ruby texture */
  up_menu.ruby = loadImageTexture("assets/images/ruby_single.png");

  /* laser_upgrade  */
  up_menu.laser_upgrade = makeUpgradeButton(3, 3, laser_pos); 
  up_menu.laser_upgrade.title_text = "Laser Regeneration";
  updateUpgradeButton(up_menu.laser_upgrade);
  up_menu.laser_upgrade.mouseover_text = loadText(path, "Laser Regeneration");
  up_menu.laser_upgrade.cost = 0;
  up_menu.laser_upgrade.upgrade = LASER_REGEN;

  /* laser_cost */
  up_menu.laser_cost = makeUpgradeButton(3, 3, laserCost_pos);
  up_menu.laser_cost.title_text = "Laser Cost";
  updateUpgradeButton(up_menu.laser_cost);
  up_menu.laser_cost.mouseover_text = loadText(path, "Laser Cost");
  up_menu.laser_cost.cost = 5;
  up_menu.laser_cost.upgrade = LASER_COST;

  /* move_speed */
  up_menu.move_speed = makeUpgradeButton(3, 3, moveSpeed_pos);
  up_menu.move_speed.title_text = "Move Speed";
  updateUpgradeButton(up_menu.move_speed);
  up_menu.move_speed.mouseover_text = loadText(path, "Move Speed");
  up_menu.move_speed.cost = 15;
  up_menu.move_speed.upgrade = MOVE_SPEED;

  /* laser_split */
  up_menu.laser_split = makeUpgradeButton(3, 1, laserSplit_pos);
  up_menu.laser_split.title_text = "Laser Split";
  updateUpgradeButton(up_menu.laser_split);
  up_menu.laser_split.mouseover_text = loadText(path, "Laser Split");
  up_menu.laser_split.cost = 25;
  up_menu.laser_split.upgrade = LASER_SPLIT;

	/* exit */
  up_menu.exit = makeButton(2, exit_pos);
  up_menu.exit.title = "Exit";
  setButtonTextures(colors, &up_menu.exit);
  up_menu.quit = false;
}

void drawUpgradeMenu(int currency) {
  SDL_Rect currency_pos = {920, 15, 30, 30};
	if(up_menu.laser_upgrade.button.textures[0] == NULL) {
		printf("Does not exist\n");
	}
  drawUpgradeButton(up_menu.laser_upgrade);
  drawUpgradeButton(up_menu.laser_cost);
  drawUpgradeButton(up_menu.move_speed);
  drawUpgradeButton(up_menu.laser_split);
  drawButton(up_menu.exit);
  drawUpgradeText(up_menu.laser_upgrade);
  drawUpgradeText(up_menu.laser_cost);
  drawUpgradeText(up_menu.move_speed);
  drawUpgradeText(up_menu.laser_split);
  drawPlayerCurrency(currency, &currency_pos);
}


void updateUpgradeMenu() {
  SDL_Color black = {0, 0, 0, 255};
  renderPresent();
  setDrawColor(black);
  clearRender();
  SDL_Delay(10);
}

void cleanupUpgradeMenu() {
	printf("Cleanup Upgrade Menu Called\n");
  destroyButton(&up_menu.laser_upgrade.button);
  destroyButton(&up_menu.move_speed.button);
  destroyButton(&up_menu.laser_split.button);
  destroyButton(&up_menu.laser_cost.button);
  destroyButton(&up_menu.exit);
}
void resetUpgradeMenu() {
  up_menu.laser_upgrade.clicked = 0;
  up_menu.laser_split.clicked = 0;
  up_menu.move_speed.clicked = 0;
  up_menu.laser_cost.clicked = 0;
}

bool updateTimesClicked(UpgradeButton* const button,
    Player* const p) {

  if(button -> clicked < button -> max_clicks
      && p -> currency >= button -> cost) {
    button -> clicked++;
    p -> currency -= button -> cost;
    if(button -> clicked == button -> max_clicks) {
      button -> upgraded = true;
    }
    return true;
  }
  else return false;
}

void handleUpgradeCheck(SDL_MouseButtonEvent e, UpgradeButton &b, Player* p) {
  if(e.button == SDL_BUTTON_LEFT) {
    if(b.button.selected) {
      bool u = updateTimesClicked(&b, p);
      updateUpgradeButton(b);
      if(u) {
        playerHandleUpgrades(b.upgrade, p);
      }
    }
  }
}
void mousePressUpgrades(SDL_MouseButtonEvent b,
                                   Player* const p) {
  handleUpgradeCheck(b, up_menu.laser_upgrade, p);
  handleUpgradeCheck(b, up_menu.laser_cost, p);
  handleUpgradeCheck(b, up_menu.move_speed, p);
  handleUpgradeCheck(b, up_menu.laser_split, p);
  if(up_menu.exit.selected) {
    up_menu.quit = true;
  } else {
    up_menu.quit = false;
  }
}
void mouseSelectUpgrades() {
  checkMouseoverState(up_menu.laser_upgrade.button);
  checkMouseoverState(up_menu.laser_cost.button);
  checkMouseoverState(up_menu.move_speed.button);
  checkMouseoverState(up_menu.laser_split.button);
  checkMouseoverState(up_menu.exit);
}

void drawUpgradeButton(UpgradeButton b) {
  if(b.upgraded) {
    renderTexture(b.button.textures[2],
        NULL, &b.button.pos);
  }
  else if(b.button.selected) {
    renderTexture(b.button.textures[1],
          NULL, &b.button.pos);
  }
  else {
    renderTexture(b.button.textures[0],
        NULL, &b.button.pos);
  }
}

void drawUpgradeText(UpgradeButton b) {
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  if(b.button.selected) {
    renderTextBox(mouse_x, mouse_y, b.mouseover_text);
  }
}

void updateUpgradeButton(UpgradeButton &b) {
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color green = {144, 245, 0, 255};
  SDL_Color yellow = {255, 255, 0, 255};
  SDL_Color colors[3];
  colors[0] = white;
  colors[1] = green;
  colors[2] = yellow;
  std::stringstream buffer;
  buffer << b.title_text;
  buffer << " (" << b.clicked << "/" << b.max_clicks << ")";
  b.button.title = buffer.str();
  setButtonTextures(colors, &b.button);
}

UpgradeButton makeUpgradeButton(int num_tex,
    int max_clicks,
    SDL_Rect pos) {
  
  UpgradeButton u;
  u.upgraded = false;
  u.max_clicks = max_clicks;
  u.clicked = 0;

  u.button = makeButton(num_tex, pos);
  return u;
}
