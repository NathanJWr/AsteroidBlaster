#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include <vector>
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
#include "timer.h"
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
int SCREEN_W = 1024;
int SCREEN_H = 768;
bool game_init;
bool upgrade_init;

struct GameObjects {
        std::vector<Asteroid> asteroidV;
        std::vector<Bullet> bulletV;
        rubyVector rubyV;
        Player player;
        struct KeyPresses keys;
        int score;
        bool running;
        Timer level_timer;
        int asteroid_time;
        Timer asteroid_timer;
};
enum Game_States {MAIN_MENU, GAME_MENU, UPGRADE_MENU, GAME, QUIT};
enum Game_States game_state;

int gameLoop(struct GameObjects*, SDL_Event*);
void mainMenuLoop(SDL_Event* e);
void gameMenuLoop(SDL_Event* e, int);
void upgradeMenuLoop(SDL_Event* e, Player* player);
void initGameObjects(struct GameObjects*);
void cleanupGameObjects(struct GameObjects*);
void drawCalls(std::vector<Asteroid>&, Player*, std::vector<Bullet>&, rubyVector*, int);
void handleScenes(struct GameObjects*, SDL_Event*, int*);

int main() {
        SDL_Event e;
        struct GameObjects gameObjects;
        int game_outcome = -1;
        game_init = false;
        upgrade_init = false;        
        game_state = MAIN_MENU;
        initVideo();
        setupAllSprites();
        initDisplayObjects();
        srand(time(NULL));

        while(game_state != QUIT) {
                handleScenes(&gameObjects,
                                &e,
                                &game_outcome);
        }
        cleanupSpriteSurfaces();
        cleanDisplayObjects();
        killVideo();
        return 0;
}

void handleScenes(struct GameObjects* gameObjects,
                SDL_Event* e,
                int* game_outcome) {
        switch(game_state) {
                case MAIN_MENU:
                        setupMainMenu();
                        if(game_init) {
                                cleanupGameObjects(gameObjects);
                                cleanupGameDisplay();
                                game_init = false;
                        }
                        if(upgrade_init) {
                                cleanupUpgradeMenu();
                                resetUpgradeMenu();
                                upgrade_init = false;
                        }
                        mainMenuLoop(e);
                        cleanupMainMenu();
                        break;
                case GAME_MENU:
                        setupGameMenu();
                        gameMenuLoop(e, *game_outcome);
                        cleanupGameMenu();
                        break;
                case UPGRADE_MENU:
                        if(!upgrade_init) {
                                setupUpgradeMenu();
                                resetUpgradeMenu();
                                upgrade_init = true;
                        }
                        upgradeMenuLoop(e, &(gameObjects -> player));
                        break;
                case GAME:
                        if(!game_init) {
                                initGameObjects(gameObjects);
                                setupGameScreen();
                                game_init = true;
                        }
                        gameObjects -> running = true;
                        *game_outcome = gameLoop(gameObjects, e);
                        break;
                case QUIT:
                        break;
        }
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

void upgradeMenuLoop(SDL_Event* e, Player* player) {
        int decision = -1;
	printf("%d", decision);
        while(decision == -1) {
                decision = handleUpgradeMenuEvents(e, player);
                updateUpgradeMenu();
                drawUpgradeMenu(player -> currency);
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
                drawCalls(game -> asteroidV,
                                &(game -> player),
                                game -> bulletV,
                                &(game -> rubyV),
                                game -> score);
                while(delta >= 1) {
                        ticks ++;
                        gameTick(game -> asteroidV,
                                        game -> bulletV,
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


                updateTimer(&game -> asteroid_timer);
                if(isTimerDone(game -> asteroid_timer)) {
                        game->asteroidV.push_back(makeAsteroid(SCREEN_W));
                        game -> asteroid_timer = newTimer(game -> asteroid_time);
                }
                        game->asteroidV.push_back(makeAsteroid(SCREEN_W));

                if(SDL_GetTicks() - lastTimer >= 1000) {
                        lastTimer += 1000;
                        printf("Ticks: %d       Frames: %d\n",
                                ticks, frames);
                        ticks = 0;
                        frames = 0;

                        updateTimer(&game -> level_timer);
                        if(isTimerDone(game -> level_timer)) {
                                if(game -> asteroid_time > 250) {
                                        game -> asteroid_time -= 250;
                                        printf("%d", game -> asteroid_time);
                                }
                                game -> level_timer = newTimer(10000);
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

void initGameObjects(struct GameObjects* g) {
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
        g -> asteroid_time = 5000;
        g -> level_timer = newTimer(10000);
        g -> asteroid_timer = newTimer(g -> asteroid_time);
}
void cleanupGameObjects(struct GameObjects* g) {
          freeAllAsteroids(g->asteroidV);
          freeAllBullets(g->bulletV);
          rubyVector_free(&(g -> rubyV));
          playerCleanup(&(g -> player));
}

void drawCalls(std::vector<Asteroid> &bv,
                Player* p,
                std::vector<Bullet> &b,
                rubyVector* r,
                int score) {

        int i;
        for(i = 0; i < (int) bv.size(); i++) {
                drawAsteroid(&(bv[i]));
        }
        for(i = 0; i < (int) b.size(); i++) {
                drawBullet(&b[i]);
        }
        for(i = 0; i < r -> count; i++) {
                drawRuby(&r -> rubies[i]);
        }
        drawPlayer(p);
        if(p -> score > score || score == 0) {
                score = p -> score;
                drawHUD(score, p -> lives, p -> laser_percent, p -> currency);
        }
}
