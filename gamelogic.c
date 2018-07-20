#include <stdbool.h> 
#include "gamelogic.h"
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
                for(int j = 0; j < blockV -> count; j++) {
                        if(checkCollision_bullet(*blockVector_get(blockV, j),
                                                *bulletVector_get(bulletV, i))) {
                                blockV -> blocks[j].hit = true;
                                bulletVector_erase(bulletV , i);
                                player -> score++;
                        }
                }
        }
        for(int i = 0; i < blockV -> count; i++) {
                if(checkCollision_player(*blockVector_get(blockV, i), *player) 
                                && !blockV -> blocks[i].hit) {
                        player -> hit = true;
                }
        }
                                
}
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
                bulletVector_add(bv, makeBullet(p -> x + (p -> sizeX / 2), p -> y));
                k -> space = false;
        }
                                
}


bool checkCollision_bullet(struct Block block, struct Bullet bullet) {
        if(bullet.x >= block.x 
                        && bullet.x <= block.x + block.sizeX
                        && bullet.y >= block.y 
                        && bullet.y <= block.y + block.sizeY
                        && !block.hit) {
                return true;
        }
        else return false;
}

bool checkCollision_player(struct Block block, struct Player player) {
        int leftP, leftB;
        int rightP, rightB;
        int topP, topB;
        int bottomP, bottomB;

        leftP = player.x;
        rightP = player.x + player.sizeX;
        topP = player.y;
        bottomP = player.y + player.sizeY - 20;

        leftB = block.x;
        rightB = block.x + block.sizeX;
        topB = block.y;
        bottomB = block.y + block.sizeY;
        if(bottomP >= topB
                        && topP <= bottomB
                        && rightP >= leftB
                        && leftP <= rightB) {
                return true;
        }
        return false;
}
