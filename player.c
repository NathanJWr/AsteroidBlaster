#include "player.h"
void playerMoveUp(struct Player* p) {
        p -> y -= p -> dy;
}

void playerMoveDown(struct Player* p) {
        p -> y += p -> dy;
}

void playerMoveLeft(struct Player* p) {
        p -> x -= p -> dx;
}

void playerMoveRight(struct Player* p) {
        p -> x += p -> dx;
}
