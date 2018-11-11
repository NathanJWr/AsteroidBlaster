#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "gamemenu.h"
#include "display.h"
#include "menu.h"
extern TTF_Font* font;
extern int SCREEN_W;
extern int SCREEN_H;

struct GameMenuAssets game_menu;
/*
Return 0 for main_menu
Return 1 for Continue
Return 2 for Upgrades
Return -1 for nothing
*/
int mousePressGame(SDL_MouseButtonEvent b) {
  if(b.button == SDL_BUTTON_LEFT) {
    /* Main Menu Button */
    if(checkBoundaries(b.x, b.y, game_menu.menu.pos)) {
      return 0;
    }

    /* Continue Button */
    if(checkBoundaries(b.x, b.y, game_menu.cont.pos)
  && !game_menu.game_over) {
      return 1;
    }

    /* Upgrades Button */
    if(checkBoundaries(b.x, b.y, game_menu.upgrades.pos)) {
      return 2;
    }
  }
  return -1;
}

void mouseSelectGame() {
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);

  if(checkBoundaries(mouse_x, mouse_y, game_menu.cont.pos)) {
    game_menu.cont.selected = true;
  }
  else {
    game_menu.cont.selected = false;
  }

  if(checkBoundaries(mouse_x, mouse_y, game_menu.menu.pos)) {
    game_menu.menu.selected = true;
  }
  else {
    game_menu.menu.selected = false;
  }

  if(checkBoundaries(mouse_x, mouse_y, game_menu.upgrades.pos)) {
    game_menu.upgrades.selected = true;
  }
  else {
    game_menu.upgrades.selected = false;
  }
}
/*
Return 0 for main_menu
Return 1 for Continue
Retrun 2 for Upgrades
Return -1 for nothing
*/
int handleGameMenuEvents(SDL_Event* const e) {
  int button = -1;
  while(SDL_PollEvent(e)) {
    mouseSelectGame();
    if(e -> type == SDL_QUIT) {
     button = 0;
    }
    else if(e -> type == SDL_MOUSEBUTTONDOWN) {
     button = mousePressGame(e -> button);
     return button;
    }
  }
  return -1;
}
void updateGameMenuButton(Button* const b) {
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color green = {144, 245, 0, 255};
  SDL_Color red = {255, 17, 0, 255};

  int i;
  for(i = 0; i < b -> num_textures; i++) {
    if(b -> textures[i] != NULL) {
      SDL_DestroyTexture(b -> textures[i]);
    }
  }
  b -> textures[0] = createTextTexture(font,
      b -> title, white);
  b -> textures[1] = createTextTexture(font,
      b -> title, green);
  if(b -> num_textures == 3) {
    b -> textures[2] = createTextTexture(font,
       b -> title, red);
  }
}
void drawGameMenuButton(Button b) {
  if(b.selected && game_menu.game_over && b.num_textures == 3) {
    renderTexture(b.textures[2], NULL, &b.pos);
  }
  else if(b.selected) {
    renderTexture(b.textures[1], NULL, &b.pos);
  }
  else {
    renderTexture(b.textures[0], NULL, &b.pos);
  }
}

void setupGameMenu() {
  SDL_Rect menu_pos;
  SDL_Rect cont_pos;
  SDL_Rect upgrade_pos;

  menu_pos.w = 800;
  menu_pos.h = 100;
  menu_pos.x = (SCREEN_W / 2) - menu_pos.w / 2;
  menu_pos.y = (SCREEN_H / 2) + 20;
  game_menu.menu = makeButton(2, menu_pos); 
  game_menu.menu.title = "Main Menu";
  updateGameMenuButton(&game_menu.menu);

  cont_pos.w = 800;
  cont_pos.h = 100;
  cont_pos.x = (SCREEN_W / 2) - cont_pos.w / 2;
  cont_pos.y = (SCREEN_H / 2) - 200;
  game_menu.cont = makeButton(3, cont_pos);
  game_menu.cont.title = "Continue";
  updateGameMenuButton(&game_menu.cont);

  upgrade_pos.w = 800;
  upgrade_pos.h = 100;
  upgrade_pos.x = (SCREEN_W / 2) - upgrade_pos.w / 2;
  upgrade_pos.y = (SCREEN_H / 2) - 100;
  game_menu.upgrades = makeButton(2, upgrade_pos);
  game_menu.upgrades.title = "Upgrades";
  updateGameMenuButton(&game_menu.upgrades);

  game_menu.game_over = false;
}

void updateGameMenu(int game_outcome) {
  SDL_Color black = {0, 0, 0, 255};
  if(game_outcome == 1) {
    game_menu.game_over = true;
  }
  if(game_outcome == 0) {
    game_menu.game_over = false;
  }
  renderPresent();
  setDrawColor(black);
  clearRender();
}

void drawGameMenu() {
  drawGameMenuButton(game_menu.menu);
  drawGameMenuButton(game_menu.cont);
  drawGameMenuButton(game_menu.upgrades);
}

void cleanupGameMenu() {
  destroyButton(&game_menu.menu);
  destroyButton(&game_menu.cont);
  destroyButton(&game_menu.upgrades);
}
