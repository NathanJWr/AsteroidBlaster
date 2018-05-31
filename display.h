#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include "player.h"
#include "block.h"
class Display {
        public:
                bool initVideo(const int SCREEN_H, const int SCREEN_W);
                void killDisplay();
                void update();
                void renderPlayer(const Player& player);
                void renderBlock(const Block& block);
        private:
                SDL_Window* gWindow;
                SDL_Renderer* gRenderer;
};
#endif
