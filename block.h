#ifndef BLOCK_H
#define BLOCK_H
#include <stdbool.h>
struct Block {
        int x;
        int y;
        int dx;
        int dy;
        int sizeX;
        int sizeY;
        bool hit;
};

typedef struct _bVector {
        struct Block* blocks;
        int size;
        int count;
} blockVector;

struct Block makeBlock(const int SCREEN_W);
bool moveBlock(struct Block*, const int SCREEN_H);


void blockVector_init(blockVector*);
void blockVector_add(blockVector*, struct Block);
struct Block* blockVector_get(blockVector*, int index);
void blockVector_free(blockVector*);
void blockVector_erase(blockVector*, int);

#endif
