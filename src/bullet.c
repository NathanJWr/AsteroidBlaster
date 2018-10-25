#include "bullet.h"
#include <stdlib.h>
#include <stdbool.h>
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
void bulletVector_init(bulletVector* const  v) {
        v -> bullets = NULL;
        v -> size = 0;
        v -> count = 0;
}

void bulletVector_add(bulletVector* const v, Bullet b) {
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

Bullet bulletVector_get(bulletVector* const v, int index) {
        if(index >= v -> count || index < 0) {
                exit(1);
        }
        return (v -> bullets[index]);
}

void bulletVector_erase(bulletVector* const v, int index) {
        int i;
        if(index >= v -> count || index < 0) {
                exit(1);
        }
        printf("laser destroyed\n");
        destroySprite(&(v -> bullets[index].sprite));
        for(i = index; i < v -> count ; i++) {
                v -> bullets[i] = v -> bullets[i+1];
        }
        v -> count--;
}

void bulletVector_free(bulletVector* const v) {
        int i;
        for(i = 0; i < v -> count; i++) {
                destroySprite(&(v -> bullets[i].sprite));
        }
        free(v -> bullets);
        v -> size = 0;
        v -> count = 0;
}
