#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "block.h"
#include "player.h"
#include "bullet.h"
#include "settings.h"
struct KeyPresses {
        bool w;
        bool a;
        bool s;
        bool d;
        bool space;
};
bool handleEvents(SDL_Event* e, struct KeyPresses* k) {
        while(SDL_PollEvent(e) != 0) {
                if(e -> type == SDL_QUIT) {
                        return false;
                }
                if(e -> type == SDL_KEYDOWN) {
                        switch(e -> key.keysym.sym) {
                                case SDLK_w:
                                        k -> w = true;
                                        k -> s = false;
                                        k -> a = false;
                                        k -> d = false;
                                        break;
                                case SDLK_a:
                                        k -> a = true;
                                        k -> d = false;
                                        k -> w = false;
                                        k -> s = false;
                                        break;
                                case SDLK_s:
                                        k -> s = true;
                                        k -> w = false;
                                        k -> a = false;
                                        k -> d = false;
                                        break;
                                case SDLK_d:
                                        k -> d = true;
                                        k -> a = false;
                                        k -> w = false;
                                        k -> s = false;
                                        break;
                                case SDLK_SPACE:
                                        k -> space = true;
                                        break;
                        }
                }
        }
        return true;
}
void movePlayer(struct KeyPresses* k, struct Player* p, bulletVector* bv) {
        if(k -> w) {
                playerMoveUp(p);
        }
        if(k -> a) {
                playerMoveLeft(p);
        }
        if(k -> s) {
                playerMoveDown(p);
        }
        if(k -> d) {
                playerMoveRight(p);
        }
        if(k -> space) {
                bulletVector_add(bv, makeBullet(p -> x, p -> y));
                k -> space = false;
        }
                                
}
void gameTick(blockVector* blockV,
                bulletVector* bulletV,
                struct Player* player,
                struct KeyPresses* keys,
                const int SCREEN_H) {
        movePlayer(keys, player, bulletV);
        for(int i = 0; i < blockV -> count; i++) {
                if(!moveBlock(&(blockV->blocks[i]), SCREEN_H)) {
                        blockVector_erase(blockV, i);
                }
        }
        for(int i = 0; i < bulletV -> count; i++) {
                if(!moveBullet(&(bulletV -> bullets[i]), SCREEN_H)) {
                        bulletVector_erase(bulletV, i);
                }
        }
}

void drawCalls(blockVector* bv, struct Player* p, bulletVector* b) {
        for(int i = 0; i < bv->count; i++) {
                drawBlock(bv->blocks[i]);
        }
        for(int i = 0; i < b -> count; i++) {
                drawBullet(b -> bullets[i]);
        }
        drawPlayer(*p);
        
}
int main() {
        //Initialize game objects + vectors
        blockVector blockV;
        bulletVector bulletV;

        bulletVector_init(&bulletV);
        blockVector_init(&blockV);

        struct Player player = {SCREEN_W / 2, SCREEN_H / 2, 2, 2, 10, 10};
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
