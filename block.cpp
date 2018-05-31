#include "block.h"
#include <cstdlib>
Block::Block(const int SCREEN_W, const int SCREEN_H) {
        sizeX = (std::rand() % 51) +50;
        sizeY = (std::rand() % 151) +50;
        xPos = (std::rand() % SCREEN_W);
        yPos = 0;
        dy = 0;
        while(dy == 0) {
                dy = (std::rand() % 1) + 1;
        }
}

void Block::move() {
        yPos += dy;
}

const int Block::getXPos() const {
        return xPos;
}

const int Block::getYPos() const {
        return yPos;
}

const int Block::getSizeX() const {
        return sizeX;
}

const int Block::getSizeY() const {
        return sizeY;
}
