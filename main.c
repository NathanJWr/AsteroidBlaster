#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "block.h"
#include "player.h"
#include "bullet.h"
#include "gamelogic.h"
const int SCREEN_W = 1024;
const int SCREEN_H = 768;
int score = 0;
void drawCalls(blockVector* bv, struct Player* p, bulletVector* b) {
        for(int i = 0; i < bv->count; i++) {
                drawBlock(bv->blocks[i]);
        }
        for(int i = 0; i < b -> count; i++) {
                drawBullet(b -> bullets[i]);
        }
        drawPlayer(*p);
        if(p -> score > score) {
                score = p -> score;
                drawScore(score);
        }
}
int main() {
        //Initialize game objects + vectors
        blockVector blockV;
        bulletVector bulletV;

        bulletVector_init(&bulletV);
        blockVector_init(&blockV);

        struct Player player = {SCREEN_W / 2, SCREEN_H / 2, 2, 2, 10, 10, false, 0};
        struct KeyPresses keys = {false, false, false, false};

        //Game loop vars
        int ticks = 0;
        int frames = 0;
        double delta = 0;
        bool running = true;
        double lastTime = SDL_GetTicks();
        double nPerTick = 1000.0/60.0;
        double lastTimer = SDL_GetTicks();

        SDL_Event e;
        initVideo(SCREEN_W, SCREEN_H);

        //Main Loop
        while(running) {
                double now = SDL_GetTicks();
                delta += (now - lastTime)/nPerTick;
                lastTime = now;
                while(delta >= 1) {
                        ticks++;
                        gameTick(&blockV, &bulletV, &player, &keys, SCREEN_H);
                        running = handleEvents(&e, &keys);
                        if(player.hit) {
                                running = false;
                        }
                        delta--;
                }
                SDL_Delay(1);
                frames++;
                updateScreen();
                drawCalls(&blockV, &player, &bulletV);

                if(SDL_GetTicks() - lastTimer >= 1000) {
                        lastTimer += 1000;
                        printf("Ticks: %d   Frames: %d\n",
                                        ticks, frames);
                        ticks = 0;
                        frames = 0;
                        if(blockV.count < 10) {
                                blockVector_add(&blockV,makeBlock(SCREEN_W));
                        }
                }
        }

        //Shutdown
        killVideo();
        blockVector_free(&blockV);
        bulletVector_free(&bulletV);
        return 0;
}
