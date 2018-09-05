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
        player.hitX= player.x + 17;
        player.hitY = player.y + 17;
        player.hitW = player.sizeX - 35;
        player.hitH = player.sizeY - 45;
        setupPlayerSprite(&player.player);
        setupHeartSprite(&player.heart);
        player.lives = 3;

        //Upgrades
        player.laser_regen = 1;
        player.move_speed = 1;
        return player;
}
void playerMoveUp(struct Player* p) {
        if(p -> y  > 0){
                p -> y -= p -> dy;
                p -> hitY -= p -> dy;
        }
}

void playerHandleUpgrades(Player_Upgrades upgrade, struct Player* player) {
        switch(upgrade) {
                case LASER_REGEN:
                        player -> laser_regen++;
                        break;
                case MOVE_SPEED:
                        player -> dx += 1;
                        player -> dy += 1;
                        break;
                case NONE:
                        break;
        }
}

void playerMoveDown(struct Player* p) {
        if(p -> y + p -> sizeY < SCREEN_H) {
                p -> y += p -> dy;
                p -> hitY += p -> dy;
        }
}

void playerMoveLeft(struct Player* p) {
        if(p -> x > 0) {
                p -> x -= p -> dx;
                p -> hitX -= p -> dx;
        }
}

void playerMoveRight(struct Player* p) {
        if(p -> x + p -> sizeX < SCREEN_W) {
                p -> x += p -> dx;
                p -> hitX += p -> dx;
        }
}
void playerCleanup(struct Player* p) {
        destroySprite(&(p -> player));
        destroySprite(&(p -> heart));
        p -> lives = 3;
        p -> hit = false;
}
