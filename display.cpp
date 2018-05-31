#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "display.h"
#include "block.h"
#include "bullet.h"
bool Display::initVideo(const int SCREEN_H, const int SCREEN_W) {
        bool success = true;
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
                success = false;
        }
        else if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                std::cout << "Linear filtering not enabled!";
        }
        gWindow = SDL_CreateWindow("Game",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        SCREEN_W,
                        SCREEN_H,
                        SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
                success = false;
        }
        else {
                gRenderer = SDL_CreateRenderer(gWindow,
                                -1,
                                SDL_RENDERER_ACCELERATED);
                if(gRenderer == NULL) {
                        success = false;
                }
                else {
                        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                }
        }
        return success;
}

void Display::killDisplay() {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);

        gRenderer = nullptr;
        gWindow = nullptr;

        SDL_Quit();
}

void Display::renderPlayer(const Player& player) {
        SDL_SetRenderDrawColor(gRenderer,238,130,238,0xFF);
        SDL_Rect rect = {player.getXPos(),
                player.getYPos(),
                player.getSizeX(),
                player.getSizeY()};

        std::vector<SDL_Rect> bullets;
        std::vector<Bullet> shots = player.getShots();
        for(int i = 0; i < (int) shots.size(); i++) {
               bullets.push_back(SDL_Rect());
               bullets.at(i).x = shots.at(i).getXPos();
               bullets.at(i).y = shots.at(i).getYPos();
               bullets.at(i).w = 5;
               bullets.at(i).h = 5;
               SDL_RenderFillRect(gRenderer, &bullets.at(i));
        }
        SDL_RenderFillRect(gRenderer, &rect);
}

void Display::renderBlock(const Block& block) {
        SDL_SetRenderDrawColor(gRenderer, 102, 255, 102, 0xFF);
        SDL_Rect rect = {
                block.getXPos(),
                block.getYPos(),
                block.getSizeX(),
                block.getSizeY()};
        SDL_RenderFillRect(gRenderer, &rect);
}

void Display::update() {
        SDL_RenderPresent(gRenderer);

        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
        SDL_RenderClear( gRenderer );
}

