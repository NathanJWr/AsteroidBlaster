#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include "display.h"
#include "asteroid.h"
#include "player.h"
#include "bullet.h"
#include "gamelogic.h"
#include "gamedisplay.h"
#include "mainmenu.h"
#include "gamemenu.h"
#include "upgrademenu.h"
#include "sprite.h"
#include "currency.h"
const int SCREEN_W = 1024;
const int SCREEN_H = 768;
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
enum Game_States {MAIN_MENU, GAME_MENU, UPGRADE_MENU, GAME, QUIT};
enum Game_States game_state;
struct GameObjects {
        asteroidVector asteroidV;
        bulletVector bulletV;
        rubyVector rubyV;
        struct Player player;
        struct KeyPresses keys;
        int score;
        bool running;
};

void initGameObjects(struct GameObjects* g) {
        asteroidVector_init(&(g -> asteroidV));
        bulletVector_init(&(g -> bulletV));
        rubyVector_init(&(g -> rubyV));
        g -> player = makePlayer();
        g -> keys.w = false;
        g -> keys.a = false;
        g -> keys.s = false;
        g -> keys.d = false;
        g -> keys.space = false;
        g -> keys.escape = false;
        g -> score = 0;
        g -> running = false;
}
void cleanupGameObjects(struct GameObjects* g) {
          asteroidVector_free(&(g -> asteroidV));
          bulletVector_free(&(g -> bulletV));
          rubyVector_free(&(g -> rubyV));
          playerCleanup(&(g -> player));
}

void drawCalls(asteroidVector* bv, struct Player* p, bulletVector* b, rubyVector* r, int score) {
        for(int i = 0; i < bv->count; i++) {
                drawAsteroid(&(bv->asteroids[i]));
        }
        for(int i = 0; i < b -> count; i++) {
                drawBullet(b -> bullets[i]);
        }
        for(int i = 0; i < r -> count; i++) {
                drawRuby(r -> rubies[i]);
        }
        drawPlayer(*p);
        if(p -> score > score || score == 0) {
                score = p -> score;
                drawHUD(score, p -> lives, p -> laser_percent, p -> currency);
        }
}


int gameLoop(struct GameObjects*, SDL_Event*);
void mainMenuLoop(SDL_Event* e);
void gameMenuLoop(SDL_Event* e, int game_outcome);
void upgradeMenuLoop(SDL_Event* e, struct Player* player);
int main() {
        bool game_init = false;
        bool upgrade_init = false;
        setupAllSprites();
        game_state = MAIN_MENU;
        initVideo(SCREEN_W, SCREEN_H);
        struct GameObjects gameObjects;
        setupGameScreen();
        SDL_Event e;
        int game_outcome;
        srand(time(NULL));


        while(game_state != QUIT) {
                switch(game_state) {
                        case MAIN_MENU:
                                setupMainMenu();
                                if(game_init) {
                                        cleanupGameObjects(&gameObjects);
                                        game_init = false;
                                }
                                if(upgrade_init) {
                                        cleanupUpgradeMenu();
                                        resetUpgradeMenu();
                                        upgrade_init = false;
                                }
                                mainMenuLoop(&e);
                                cleanupMainMenu();
                                break;
                        case GAME_MENU:
                                setupGameMenu();
                                gameMenuLoop(&e, game_outcome);
                                cleanupGameMenu();
                                break;
                        case UPGRADE_MENU:
                                if(!upgrade_init) {
                                        setupUpgradeMenu();
                                        resetUpgradeMenu();
                                        upgrade_init = true;
                                }
                                upgradeMenuLoop(&e, &(gameObjects.player));
                                break;
                        case GAME:
                                if(!game_init) {
                                        initGameObjects(&gameObjects);
                                        game_init = true;
                                }
                                gameObjects.running = true;
                                game_outcome = gameLoop(&gameObjects, &e);
                                break;
                        case QUIT:
                                break;
                                
                }
        }
        cleanupGameDisplay();
        cleanupSpriteSurfaces();
        killVideo();
        return 0;
}
void mainMenuLoop(SDL_Event* e) {
        int decision = -1;
        while(decision == -1) {
                drawMainMenu();
                updateMainMenu();
                decision = handleMainMenuEvents(e);
        }
        if(decision == 0) {
                game_state = QUIT;
        }
        else if(decision == 1) {
                game_state = GAME;
        }
}
void gameMenuLoop(SDL_Event* e, int game_outcome) {
        int decision = -1;
        while(decision == -1) {
                drawGameMenu();
                updateGameMenu(game_outcome);
                decision = handleGameMenuEvents(e);
        }
        if(decision == 0) {
                game_state = MAIN_MENU;
        }
        else if(decision == 1) {
                game_state = GAME;
        }
        else if(decision == 2) {
                game_state = UPGRADE_MENU;
        }
}
void upgradeMenuLoop(SDL_Event* e, struct Player* player) {
        int decision = -1;
        while(decision == -1) {
                decision = handleUpgradeMenuEvents(e, player);
                updateUpgradeMenu();
                drawUpgradeMenu();
        }
        game_state = GAME_MENU;
}
int gameLoop(struct GameObjects* game, SDL_Event* e) {
        int ticks = 0;
        int frames = 0;
        double delta = 0;
        double lastTime = SDL_GetTicks();
        double nPerTick = 1000.0/60.0;
        double lastTimer = SDL_GetTicks();
        while(game -> running) {
                double now = SDL_GetTicks();
                delta += (now - lastTime) / nPerTick;
                lastTime = now;
                updateGameScreen();
                drawCalls(&(game -> asteroidV),
                                &(game -> player),
                                &(game -> bulletV),
                                &(game -> rubyV),
                                game -> score);
                while(delta >= 1) {
                        ticks ++;
                        gameTick(&(game -> asteroidV),
                                        &(game -> bulletV),
                                        &(game -> rubyV),
                                        &(game -> player),
                                        &(game -> keys),
                                        SCREEN_H);
                        game -> running = handleEvents(e, &(game -> keys));
                        if(game -> player.lives == 0) {
                                game -> running = false;
                        }
                        delta--;
                }
                SDL_Delay(1);
                frames++;
                if(SDL_GetTicks() - lastTimer >= 1000) {
                        lastTimer += 1000;
                        printf("Ticks: %d       Frames: %d\n",
                                ticks, frames);
                        ticks = 0;
                        frames = 0;
                        if(game -> asteroidV.count < 10) {
                                asteroidVector_add(&(game -> asteroidV),
                                                makeAsteroid(SCREEN_W));
                        }
                }
                if(game -> keys.escape) {
                        game -> running = false;
                }
        }
        game -> keys.escape = false;
        game_state = GAME_MENU;
        if(game -> player.lives <= 0) {
                return 1;
        }
        else {
                return 0;
        }
}
