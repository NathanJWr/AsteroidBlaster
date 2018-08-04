#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "display.h"
#include "asteroid.h"
#include "player.h"
#include "bullet.h"
#include "gamelogic.h"
#include "gamedisplay.h"
#include "menu.h"

const int SCREEN_W = 1024;
const int SCREEN_H = 768;
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;

enum Game_States {MENU, GAME, QUIT};
enum Game_States game_state;
int score = 0;
void drawCalls(asteroidVector* bv, struct Player* p, bulletVector* b) {
        for(int i = 0; i < bv->count; i++) {
                drawAsteroid(bv->asteroids[i]);
        }
        for(int i = 0; i < b -> count; i++) {
                drawBullet(b -> bullets[i]);
        }
        drawPlayer(*p);
        if(p -> score > score || score == 0) {
                score = p -> score;
                drawScore(score);
        }
}

void gameLoop(SDL_Event* e);
void menuLoop(SDL_Event* e);
int main() {
        game_state = MENU;
        initVideo(SCREEN_W, SCREEN_H);
        setupMenu();
        SDL_Event e;
        setupGameSprites();
        
        while(game_state != QUIT) {
                if(game_state == MENU) {
                        menuLoop(&e);
                }
                else if(game_state == GAME) {
                        gameLoop(&e);
                }
        }
        cleanupMenuScreen();
        cleanupGameDisplay();
        killVideo();
        return 0;
}
void menuLoop(SDL_Event* e) {
        int decision = -1;
        while(decision == -1) {
                drawMenu();
                updateMenuScreen();
                decision = handleMenuEvents(e);
        }
        if(decision == 0) {
                game_state = QUIT;
        }
        else if(decision == 1) {
                game_state = GAME;
        }
}
void gameLoop(SDL_Event* e) {
        asteroidVector asteroidV;
        asteroidVector_init(&asteroidV);
        bulletVector bulletV;
        bulletVector_init(&bulletV);

        struct Player player = makePlayer(); 
        struct KeyPresses keys = {false, false, false, false};

        int ticks = 0;
        int frames = 0;
        double delta = 0;
        double lastTime = SDL_GetTicks();
        double nPerTick = 1000.0/60.0;
        double lastTimer = SDL_GetTicks();
        bool running = true;
        while(running) {
                double now = SDL_GetTicks();
                delta += (now - lastTime) / nPerTick;
                lastTime = now;
                while(delta >= 1) {
                        ticks ++;
                        gameTick(&asteroidV, &bulletV, &player, &keys, SCREEN_H);
                        running = handleEvents(e, &keys);
                        if(player.hit) {
                                running = false;
                        }
                        delta--;
                }
                SDL_Delay(1);
                frames++;
                updateGameScreen();
                drawCalls(&asteroidV, &player, &bulletV);

                if(SDL_GetTicks() - lastTimer >= 1000) {
                        lastTimer += 1000;
                        printf("Ticks: %d       Frames: %d\n",
                                ticks, frames);
                        ticks = 0;
                        frames = 0;
                        if(asteroidV.count < 10) {
                                asteroidVector_add(&asteroidV, makeAsteroid(SCREEN_W));
                        }
                }
        }
        score = 0;              
        asteroidVector_free(&asteroidV);
        bulletVector_free(&bulletV);
        game_state = MENU;
}
