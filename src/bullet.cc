#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include "bullet.h"
#include "sprite.h"
extern int SCREEN_W;
Bullet makeBullet(int x, int y, int dx, int dy) {
        Bullet b;
        b.x = x;
        b.y = y;
        b.dx = dx;
        b.dy = dy;
        b.sizeX = 30;
        b.sizeY = 30;

        b.hitX = x - 5;
        b.hitY = y;
        b.hitW = 10;
        b.hitH = 30;
        setupBulletSprite(&b.sprite);
        return b;
}
bool moveBullet(Bullet* const b) {
        b -> y -= b -> dy;
        b -> hitY -= b -> dy;
        b -> x += b -> dx;
        b -> hitX += b -> dx;
        if(b -> y <= 0) {
                return false;
        }
        else if(b -> x <= 0 || b -> x >= SCREEN_W) {
                return false;
        }
        else return true;
}
void eraseBullet(std::vector<Bullet>& vec, const int index) {
        destroySprite(&vec[index].sprite);
        vec.erase(vec.begin() + index);
}
void freeAllBullets(std::vector<Bullet>& vec) {
        for(Bullet &n : vec) {
                destroySprite(&n.sprite);
        }
        vec.clear();
}

