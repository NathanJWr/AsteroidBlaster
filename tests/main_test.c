#include <stdbool.h>
#include "display.h"
#include "block.h"
#include "settings.h"
int main() {
        blockVector bv;
        blockVector_init(&bv);
        blockVector_add(&bv, makeBlock(SCREEN_W));
        blockVector_add(&bv, makeBlock(SCREEN_W));
        blockVector_add(&bv, makeBlock(SCREEN_W));
        blockVector_add(&bv, makeBlock(SCREEN_W));
        blockVector_add(&bv, makeBlock(SCREEN_W));
        blockVector_add(&bv, makeBlock(SCREEN_W));
        blockVector_free(&bv);
        return 0;
}
