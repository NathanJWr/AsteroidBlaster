#include "gamelogic.h"
#include "player.h"
#include "block.h"
#include "keyboardhandler.h"
#include "settings.h"
#include <SDL2/SDL.h>

void GameLogic::tick(Player& player,
                std::vector<Block>& blocks,
                SDL_Event& e,
                KeyboardHandler& kbhandler) {
        for(auto& block : blocks) {
                block.move();
                handleBlocks(blocks);
        }
        player.moveBullets(SCREEN_H, SCREEN_W);
        kbhandler.handleKeyboardEvent(e);
        if(kbhandler.isPressed('w')) {
                player.moveUp();
        }
        if(kbhandler.isPressed('s')) {
                player.moveDown();
        }
        if(kbhandler.isPressed('a')) {
                player.moveLeft();
        }
        if(kbhandler.isPressed('d')) {
                player.moveRight();
        }
        if(kbhandler.isPressed(' ')) {
                player.shoot();
                kbhandler.resetShot();
        }

}

void GameLogic::handleBlocks(std::vector<Block>& blocks) {
        for(int i = 0; i < (int) blocks.size(); i++) {
                if(blocks.at(i).getYPos() > SCREEN_H) {
                        blocks.erase(blocks.begin() + i);
                        blocks.push_back(Block(SCREEN_W, SCREEN_H));
                }
        }
}

void GameLogic::genBlock(std::vector<Block>& blocks) {
        blocks.push_back(Block(SCREEN_H, SCREEN_W));
}


