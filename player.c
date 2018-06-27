#include "player.h"
extern const int SCREEN_W;
extern const int SCREEN_H;
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
