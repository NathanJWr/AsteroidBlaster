#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include "player.h"
#include "block.h"
#include "keyboardhandler.h"
class GameLogic {
        public:
                void tick(Player& player,
                                std::vector<Block>& blocks,
                                SDL_Event& e,
                                KeyboardHandler& kbhandler);
                void genBlock(std::vector<Block>& blocks);
        private:
                void handleBlocks(std::vector<Block>& blocks);

};
#endif
