#include "display.h"
#include "settings.h"
#include "player.h"
#include "block.h"
#include "keyboardhandler.h"
#include "gamelogic.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <SDL2/SDL.h>
int main() {
        std::srand(std::time(nullptr));
        Display display;
        SDL_Event e;
        KeyboardHandler kbhandler;
        GameLogic game;
        display.initVideo(SCREEN_H, SCREEN_W);

        std::vector<Block> blocks;
        int numBlocks = 0;


        Player player(SCREEN_W, SCREEN_H);
        //int i = 0;

        int ticks = 0;
        int frames = 0;

        double delta = 0;
        bool running = true;
        double lastTime = SDL_GetTicks();
        double nPerTick = 1000.0f/60.0f;
        long lastTimer = SDL_GetTicks();
        while(running) {
                int now = SDL_GetTicks();
                delta += (now - lastTime)/nPerTick;
                lastTime = now;
                while(delta >= 1) {
                        ticks++;
                        game.tick(player, blocks, e, kbhandler);
                        delta--;
                }
                SDL_Delay(2);
                frames++;
                display.renderPlayer(player);
                for(auto& block : blocks) {
                        display.renderBlock(block);
                }
                display.update();

               

                if(SDL_GetTicks() - lastTimer >= 1000) {
                        lastTimer += 1000;
                        std::cout << "Ticks: " << ticks << 
                                "       Frames: " << frames 
                                << "    B: " << blocks.size() << std::endl;

                        ticks = 0;
                        frames = 0;
                        if(numBlocks < 10) {                        
                                game.genBlock(blocks);
                                numBlocks++;
                        }
                }
                if(e.type == SDL_QUIT) {
                        running = false;
                }
        }
        display.killDisplay();
        return 0;
}
