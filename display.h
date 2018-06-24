#ifndef DISPLAY_H
#define DISPLAY_H
#include "block.h"
#include "player.h"
        bool initVideo();
        void updateScreen();
        void killVideo();
        void drawBlock(struct Block block);
        void drawPlayer(struct Player player);
#endif
