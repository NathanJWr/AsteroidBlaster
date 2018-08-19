#include "player.h"
extern const int SCREEN_W;
extern const int SCREEN_H;
struct Player makePlayer() {
        struct Player player;
        player.x = SCREEN_W / 2;
        player.y = SCREEN_H / 2;
        player.dx = 2;
        player.dy = 2;
        player.sizeX = 100;
        player.sizeY = 100;
        player.hit = false;
        player.score = 0;
        player.laser_percent = 100;
        player.hitbox.x = player.x + 17;
        player.hitbox.y = player.y + 17;
        player.hitbox.w = player.sizeX - 35;
        player.hitbox.h = player.sizeY - 45;
        setupPlayerSprite(&player.sprite);
        return player;
}
void playerMoveUp(struct Player* p) {
        if(p -> y  > 0){
                p -> y -= p -> dy;
                p -> hitbox.y -= p -> dy;
        }
}

void playerMoveDown(struct Player* p) {
        if(p -> y + p -> sizeY < SCREEN_H) {
                p -> y += p -> dy;
                p -> hitbox.y += p -> dy;
        }
}

void playerMoveLeft(struct Player* p) {
        if(p -> x > 0) {
                p -> x -= p -> dx;
                p -> hitbox.x -= p -> dx;
        }
}

void playerMoveRight(struct Player* p) {
        if(p -> x + p -> sizeX < SCREEN_W) {
                p -> x += p -> dx;
                p -> hitbox.x += p -> dx;
        }
}
void playerCleanup(struct Player* p) {
        destroySprite(&(p -> sprite));
}
