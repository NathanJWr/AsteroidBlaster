#include "bullet.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct Bullet makeBullet(int x, int y) {
        struct Bullet b = {x, y, 5, 5, 3, 3};
        return b;
}
bool moveBullet(struct Bullet* b, const int SCREEN_H) {
        b -> y -= b -> dy;
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

void bulletVector_erase(bulletVector* v, int index) {
        printf("called");
        if(index >= v -> size || index < 0) {
                exit(1);
        }
        for(int i = index; i < v -> count ; i++) {
                v -> bullets[i] = v -> bullets[i+1];
        }
        printf("%d", v -> count);
        v -> count--;
}

void bulletVector_free(bulletVector* v) {
        free(v -> bullets);
        v -> size = 0;
        v -> count = 0;
}
