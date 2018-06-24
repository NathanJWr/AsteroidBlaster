#include "block.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct Block makeBlock(const int SCREEN_W) {
        struct Block b;
        b.x = rand() % SCREEN_W;
        b.y = 0;
        b.sizeX = (rand() % 51) + 50;
        b.sizeY = (rand() % 151) + 50;
        b.dy = 0;
        while(b.dy == 0) {
                b.dy = (rand() % 1) + 1;
        }
        return b;
}

bool moveBlock(struct Block* block, const int SCREEN_H) {
        block -> y += block -> dy;
        if(block -> y > SCREEN_H) {
                return false;
        }
        else return true;
}

void blockVector_init(blockVector* v) {
        v->blocks = NULL;
        v->size = 0;
        v->count = 0;
}

void blockVector_add(blockVector* v, struct Block b) {
        if(v->size == 0) {
                v->size = 10;
                v->blocks = malloc(sizeof(b) * v->size);
                memset(v->blocks, '\0', sizeof(b) * v->size);
        }
        if(v->size == v->count) {
                v->size *= 2;
                v->blocks = realloc(v->blocks, sizeof(b) * v->size);
        }
        v->blocks[v->count] = b;
        v->count++;
}

struct Block* blockVector_get(blockVector* v, int index) {
        if(index >= v->size || index < 0) {
                exit(1);
        }
        return &(v->blocks[index]);
}

void blockVector_erase(blockVector* v, int index) {
        if(index >= v->size || index < 0) {
                exit(1);
        }
        v->blocks[index] = makeBlock(1024);
}

void blockVector_free(blockVector* v) {
        free(v->blocks);
        v->size = 0;
        v->count = 0;
}
