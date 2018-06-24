#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "block.h"
#include "player.h"
#include "settings.h"
struct KeyPresses {
        bool w;
        bool a;
        bool s;
        bool d;
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
                        }
                }
        }
        return true;
}
void movePlayer(struct KeyPresses* k, struct Player* p) {
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
}
void gameTick(blockVector* bv, int SCREEN_H) {
        for(int i = 0; i < bv->count; i++) {
                if(!moveBlock(&(bv->blocks[i]), SCREEN_H)) {
                        blockVector_erase(bv, i);
                }
        }
}

void drawCalls(blockVector* bv, struct Player* p) {
        for(int i = 0; i < bv->count; i++) {
                drawBlock(bv->blocks[i]);
        }
        drawPlayer(*p);
}
int main() {
        //Initialize game objects + vectors
        blockVector bv;
        blockVector_init(&bv);
        struct Player player = {SCREEN_W / 2, SCREEN_H / 2, 2, 2, 10, 10};
        struct KeyPresses keys = {false, false, false, false};

        //Game loop vars
        int ticks = 0;
        int frames = 0;
        double delta = 0;
        bool running = true;
        double lastTime = SDL_GetTicks();
        double nPerTick = 1000.0f/60.0f;
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
                        gameTick(&bv, SCREEN_H);
                        running = handleEvents(&e, &keys);
                        movePlayer(&keys, &player);
                        updateScreen();
                        delta--;
                }
                SDL_Delay(3);
                frames++;
                drawCalls(&bv, &player);

                if(SDL_GetTicks() - lastTimer >= 1000) {
                        lastTimer += 1000;
                        printf("Ticks: %d   Frames: %d\n",
                                        ticks, frames);
                        ticks = 0;
                        frames = 0;
                        if(bv.count < 10) {
                                blockVector_add(&bv,makeBlock(SCREEN_W));
                        }
                }
        }

        //Shutdown
        killVideo();
        blockVector_free(&bv);
        return 0;
}
