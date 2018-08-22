#include "bullet.h"
#include <stdlib.h>
#include <stdbool.h>
#include "sprite.h"
struct Bullet makeBullet(int x, int y) {
        struct Bullet b;
        b.x = x;
        b.y = y;
        b.dx = 3;
        b.dy = 3;
        b.sizeX = 30;
        b.sizeY = 30;

        b.hitX = x - 5;
        b.hitY = y;
        b.hitW = 10;
        b.hitH = 30;
        setupBulletSprite(&b.sprite);
        return b;
}
bool moveBullet(struct Bullet* b, const int SCREEN_H) {
        b -> y -= b -> dy;
        b -> hitY -= b -> dy;
        if(b -> y <= 0) {
                return false;
        }
        else return true;
}
void bulletVector_init(bulletVector* v) {
        v -> bullets = NULL;
        v -> size = 0;
        v -> count = 0;
}

void bulletVector_add(bulletVector* v, struct Bullet b) {
        if(v -> size == 0) {
                v -> size = 10;
                v -> bullets = malloc(sizeof(b) * v -> size);
        }
        if(v -> size == v -> count) {
                v -> size *= 2;
                v -> bullets = realloc(v -> bullets, sizeof(b) * v -> size);
        }
        v -> bullets[v -> count] = b;
        v -> count++;
}

struct Bullet* bulletVector_get(bulletVector* v, int index) {
        if(index >= v -> size || index < 0) {
                exit(1);
        }
        return &(v -> bullets[index]);
}

void bulletVector_erase(bulletVector* v, int index) {
        if(index >= v -> size || index < 0) {
                exit(1);
        }
        destroySprite(&(v -> bullets[index].sprite));
        for(int i = index; i < v -> count ; i++) {
                v -> bullets[i] = v -> bullets[i+1];
        }
        v -> count--;
}

void bulletVector_free(bulletVector* v) {
        for(int i = 0; i < v -> count; i++) {
                destroySprite(&(v -> bullets[i].sprite));
        }
        free(v -> bullets);
        v -> size = 0;
        v -> count = 0;
}
