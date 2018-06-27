#include "player.h"
extern const int SCREEN_W;
extern const int SCREEN_H;
void playerMoveUp(struct Player* p) {
        if(p -> y  > 0){
                p -> y -= p -> dy;
        }
}

void playerMoveDown(struct Player* p) {
        if(p -> y + p -> sizeY < SCREEN_H) {
                p -> y += p -> dy;
        }
}

void playerMoveLeft(struct Player* p) {
        if(p -> x > 0) {
                p -> x -= p -> dx;
        }
}

void playerMoveRight(struct Player* p) {
        p -> x += p -> dx;
}
